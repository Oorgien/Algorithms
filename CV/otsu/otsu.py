import sys, os.path, cv2, numpy as np


def otsu(img: np.ndarray) -> np.ndarray:
    n_bins = 256
    EPS = 0.001
    if len(img.shape) == 2:
        img = img.reshape(*img.shape, 1)
    hist = cv2.calcHist([img], [0],None, histSize=[n_bins], ranges=[0,n_bins]).ravel()
    hist_norm = hist/hist.max()
    hist_P = np.cumsum(hist_norm, axis=0)

    optimal_t = 0
    min_var = np.inf
    I = np.arange(256)
    for t in range(0,256):
        p1,p2 = np.hsplit(hist_norm, [t])

        q1 = hist_P[t]
        q2 = hist_P[-1] - hist_P[t]

        is_1, is_2 = np.hsplit(I, [t])

        mean1 = np.sum(p1 * is_1)/ (q1 + EPS)
        mean2 = np.sum(p2 * is_2) / (q2 + EPS)

        var1, var2 = np.sum((is_1 - mean1)**2 * p1)/(q1 + EPS) , np.sum((is_2 - mean2)**2 * p2)/(q2 + EPS)

        var_w = q1 * var1 + q2 * var2

        if var_w < min_var:
            min_var = var_w
            optimal_t = t

    img[img < optimal_t] = 0
    img[img >= optimal_t] = 255
    return img

def main():
    assert len(sys.argv) == 3
    src_path, dst_path = sys.argv[1], sys.argv[2]

    assert os.path.exists(src_path)
    img = cv2.imread(src_path, cv2.IMREAD_GRAYSCALE)
    assert img is not None

    ret, otsu_test = cv2.threshold(img, 0, 255,cv2.THRESH_OTSU)
    cv2.imwrite('test.png', otsu_test)

    result = otsu(img)
    cv2.imwrite(dst_path, result)

if __name__ == '__main__':
    main()
