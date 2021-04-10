import sys, os.path, cv2, numpy as np
import matplotlib.pyplot as plt

def show(img):
    plt.imshow(img)
    plt.show()

def show_hough_line(img, accumulator, thetas, rhos, save_path=None):
    import matplotlib.pyplot as plt

    fig, ax = plt.subplots(1, 2, figsize=(10, 10))

    ax[0].imshow(img)
    ax[0].set_title('Input image')
    ax[0].axis('image')

    ax[1].imshow(
        accumulator, cmap='jet',
        extent=[np.rad2deg(thetas[-1]), np.rad2deg(thetas[0]), rhos[-1], rhos[0]])
    ax[1].set_aspect('equal', adjustable='box')
    ax[1].set_title('Hough transform')
    ax[1].set_xlabel('Angles (degrees)')
    ax[1].set_ylabel('Distance (pixels)')
    ax[1].axis('image')

    # plt.axis('off')
    if save_path is not None:
        plt.savefig(save_path, bbox_inches='tight')
    plt.show()

def gradient_img(img: np.ndarray) -> np.ndarray:
    hor_grad = (img[1:, :] - img[:-1, :])[:, :-1]
    ver_grad = (img[:, 1:] - img[:, :-1])[:-1:, :]
    magnitude = np.sqrt(hor_grad ** 2 + ver_grad ** 2)
    return magnitude


def hough_transform(img: np.ndarray, theta: float, rho: float) -> (np.ndarray, list, list):

    height, width = img.shape
    diag_len = np.ceil(np.sqrt(height ** 2 + width ** 2))
    rhos = np.arange(-diag_len, diag_len + 1, rho)
    thetas = np.deg2rad(np.arange(-90, 90, round(np.rad2deg(theta))))

    H = np.zeros((len(rhos), len(thetas)), dtype=np.uint64)
    are_edges = img > 5

    y_idxs, x_idxs = np.nonzero(are_edges)
    for i in range(len(x_idxs)):
        x = x_idxs[i]
        y = y_idxs[i]
        """for y in range(height):
            for x in range(width):"""
        for t_idx in range(len(thetas)):
            # Calculate rho. diag_len is added for a positive index
            rho_ = diag_len + int(round(x * np.cos(thetas[t_idx]) + y * np.sin(thetas[t_idx])))
            H[int(round(rho_/rho)), t_idx] += img[y, x]
    return H, thetas, rhos


def get_lines(img, ht_map: np.ndarray, n_lines: int,thetas: np.ndarray, rhos: np.ndarray,
              min_delta_rho: float, min_delta_theta: float) -> list:
    res_thetas = []
    res_ros = []
    res = []

    ht_map_flat = np.ravel(ht_map)
    ind = np.argsort(ht_map_flat, axis=None)[::-1]
    H1_idx = np.unravel_index(ind, ht_map.shape)

    for (i,j) in zip(H1_idx[0], H1_idx[1]):
        rho, theta = rhos[i], thetas[j]
        if not res_thetas and not res_ros:
            res_thetas.append(theta)
            res_ros.append(rho)
        if (min(np.abs(np.array(res_thetas) - theta)) > min_delta_theta
                and min(np.abs(np.array(res_ros) - rho)) > min_delta_rho):
            res_thetas.append(theta)
            res_ros.append(rho)

        if len(res_thetas) == n_lines:
            break
    """while len(ros_thetas) != n_lines:
        idx = np.argmax(ht_map)  # find argmax in flattened array
        H_idx = np.unravel_index(idx, ht_map.shape)  # remap to shape of H
        # print (H_idx[0])
        rho, theta = rhos[H_idx[0]], thetas[H_idx[1]]

        if not ros_thetas or (np.abs(ros_thetas[-1][0] - rho) > min_delta_rho and np.abs(ros_thetas[-1][1] - theta) > min_delta_theta):
            ros_thetas.append((rho, theta))
            print(ht_map[H_idx[0], H_idx[1]])
            ht_map[H_idx[0], H_idx[1]] = 0"""

    for rho, theta in zip(res_ros, res_thetas):
        a = np.cos(theta)
        b = np.sin(theta)
        k = -a/(b + 0.001)
        b = rho/(b + 0.001)
        res.append((k,b))

    # show lines
    for i in range(0, len(res_thetas)):
        rho = res_ros[i]
        theta = res_thetas[i]
        a = np.cos(theta)
        b = np.sin(theta)
        x0 = a * rho
        y0 = b * rho
        pt1 = (int(x0 + 1000 * (-b)), int(y0 + 1000 * (a)))
        pt2 = (int(x0 - 1000 * (-b)), int(y0 - 1000 * (a)))
        cv2.line(img, pt1, pt2, (0, 0, 255), 1, cv2.LINE_AA)
    show_hough_line(img, ht_map, thetas, rhos, save_path=None)
    return res


# python hough.py test.jpg res.jpg res.txt 0.01 1 10 1 0.01
def main():
    assert len(sys.argv) == 9
    src_path, dst_ht_path, dst_lines_path, theta, rho, \
        n_lines, min_delta_rho, min_delta_theta = sys.argv[1:]

    theta = float(theta)
    assert theta > 0.0

    rho = float(rho)
    assert rho > 0.0

    n_lines = int(n_lines)
    assert n_lines > 0

    min_delta_rho = float(min_delta_rho)
    assert min_delta_rho > 0.0

    min_delta_theta = float(min_delta_theta)
    # assert min_delta_theta > 0.0

    assert os.path.exists(src_path)

    img = cv2.imread(src_path, cv2.IMREAD_GRAYSCALE)
    # for faster computations
    img = cv2.resize(img, (128, 128))
    assert img is not None

    gradient = gradient_img(img.astype(float))

    ht_map, thetas, rhos = hough_transform(gradient, theta, rho)
    # show hough space plot
    show_hough_line(img, ht_map, thetas, rhos, dst_ht_path)

    lines = get_lines(img,  ht_map, n_lines, thetas,
                      rhos, min_delta_rho, min_delta_theta)

    with open(dst_lines_path, 'w') as fout:
        for line in lines:
            fout.write(f'{line[0]:.3f}, {line[1]:.3f}\n')


if __name__ == '__main__':
    main()
