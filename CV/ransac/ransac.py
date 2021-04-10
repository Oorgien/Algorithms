import sys, os.path, json, numpy as np
from numpy.random import normal, uniform, choice
from scipy.stats import invgauss, median_abs_deviation, chi2
from sklearn.linear_model import LinearRegression

def show_points(X,Y):
    import matplotlib.pyplot as plt

    fig, ax = plt.subplots(figsize=(10, 10))

    ax.scatter(X,Y)
    ax.set_title('Points')
    plt.show()

def show_result(X, y_real, x_pred, y_pred ):
    import matplotlib.pyplot as plt

    fig, ax = plt.subplots(figsize=(10, 10))

    ax.scatter(X, y_real, color='blue')
    ax.scatter(x_pred, y_pred, color='red')
    ax.legend(['y real', 'y pred'])
    ax.set_title('Points')
    plt.show()

def generate_data(
        img_size: tuple, line_params: tuple,
        n_points: int, sigma: float, inlier_ratio: float
) -> np.ndarray:
    height, width = img_size
    a, b, c = line_params
    X = []
    Y = []
    inlier_size = int(n_points * inlier_ratio)

    x_s = np.linspace(0, width-1, inlier_size)
    for i in range(inlier_size):
        E = normal(loc=0, scale=sigma)
        y = int(-(a/b) * x_s[i] - (c/b))
        X.append(x_s[i]+E)
        Y.append(y+E)
    for i in range(int(n_points * (1-inlier_ratio))):
        y, x = uniform(0, height-1), uniform(0, width-1)
        Y.append(y)
        X.append(x)
    show_points(X,Y)
    return np.array((X,Y))



def compute_ransac_threshold(
        alpha: float, sigma: float
) -> float:
    T_2 = chi2.ppf(alpha, 2) * np.power(sigma, 2)
    return T_2


def compute_ransac_iter_count(
        conv_prob: float, inlier_ratio: float,
        m: int
) -> int:
    w = inlier_ratio
    k = np.log(1-conv_prob)/np.log(1-w**m)
    return int(k)



def compute_line_ransac(
        data: np.ndarray, threshold: float, iter_count: int,
        m: int
) -> tuple:

    best_model = LinearRegression()
    X = data[0]
    Y = data[1]
    print('threshold', threshold,
           'iter count', iter_count)

    data = list(zip(X, Y))
    d_max = 0
    for i in range(iter_count):
        ind = choice(len(X), size=m)
        X_sample = X[ind]
        Y_sample = Y[ind]
        # show_points(X_sample,Y_sample )
        model = LinearRegression()
        model.fit(X_sample.reshape(-1, 1), Y_sample.reshape(-1, 1))
        maybe_inliers = list(zip(X_sample, Y_sample))

        also_inliers = []
        also_inliers_X = []
        also_inliers_Y = []
        for point in data:
            if point not in maybe_inliers:
                if np.all((model.predict(point[0].reshape(1, -1)) - point[1].reshape(1, -1))**2 < threshold):

                    also_inliers.append((point[0], point[1]))
                    also_inliers_X.append(point[0])
                    also_inliers_Y.append(point[1])

        X_sample = np.hstack((np.ravel(X_sample), np.ravel(also_inliers_X)))
        Y_sample = np.hstack((np.ravel(Y_sample), np.ravel(also_inliers_Y)))

        d = len(also_inliers)
        if d > d_max:
            best_model.fit(X_sample.reshape(-1, 1), Y_sample.reshape(-1, 1))
            d_max = d

    show_result(X, Y, X, best_model.predict(X.reshape(-1, 1)))
    return best_model.coef_, best_model.intercept_


def detect_line(params: dict) -> tuple:
    m = 2

    data = generate_data(
        (params['w'], params['h']),
        (params['a'], params['b'], params['c']),
        params['n_points'], params['sigma'], params['inlier_ratio']
    )
    threshold = compute_ransac_threshold(
        params['alpha'], params['sigma']
    )
    iter_count = compute_ransac_iter_count(
        params['conv_prob'], params['inlier_ratio'], m
    )
    detected_line = compute_line_ransac(data, threshold, iter_count, m)
    return detected_line

# python ransac.py params.json
def main():
    assert len(sys.argv) == 2
    params_path = sys.argv[1]
    assert os.path.exists(params_path)
    with open(params_path) as fin:
        params = json.load(fin)
    assert params is not None

    """
    params:
    line_params: (a,b,c) - line params (ax+by+c=0)
    img_size: (w, h) - size of the image
    n_points: count of points to be used

    sigma - Gaussian noise
    alpha - probability of point is an inlier

    inlier_ratio - ratio of inliers in the data
    conv_prob - probability of convergence
    """

    detected_line = detect_line(params)
    print(detected_line)


if __name__ == '__main__':
    main()
