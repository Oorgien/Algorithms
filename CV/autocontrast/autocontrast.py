import sys, os.path, cv2, numpy as np
import PIL
from PIL import ImageOps, Image

def autocontrast(img: np.ndarray, white_percent: float, black_percent: float) -> np.ndarray:
    channels = []
    if len(img.shape) == 2:
        img = img.reshape(*img.shape, 1)

    for i in range(img.shape[-1]):
        n_bins = 256
        hist = cv2.calcHist([img], [i], None, [n_bins], [0, n_bins])
        # plt.hist(image.ravel(), 256, [0, 256])
        # plt.show()
        n = np.sum(hist)

        blacks = black_percent * n
        whites = white_percent * n

        low = np.argwhere(np.cumsum(hist) > blacks)
        low = low[0]

        high = np.argwhere(np.cumsum(hist[::-1]) > whites)
        high = n_bins - 1 - high[0]

        if low == 256 or high == 0:
            print ('Invalid picture or parameters')
            exit(-1)

        if high <= low:
            high = low + 1
            # table = np.arange(n_bins)
        # print(low, high)
        scale = (n_bins - 1) / (high - low)
        offset = -low * scale
        table = np.arange(n_bins) * scale + offset
        table[table < 0] = 0
        table[table > n_bins - 1] = n_bins - 1
        table = table.astype(np.uint8)
        channels.append(table[img[:, :, i]])
    out = cv2.merge(channels)
    return out


def main():
    assert len(sys.argv) == 5
    src_path, dst_path = sys.argv[1], sys.argv[2]
    white_percent, black_percent = float(sys.argv[3]), float(sys.argv[4])
    assert 0 <= white_percent < 1
    assert 0 <= black_percent < 1

    assert os.path.exists(src_path)
    img = cv2.imread(src_path, cv2.IMREAD_GRAYSCALE)
    # img = np.full((800, 600), 255, dtype=np.uint8)
    # img = np.full((800, 600), 0, dtype=np.uint8)
    assert img is not None

    result = autocontrast(img, white_percent, black_percent)
    cv2.imwrite(dst_path, result)

if __name__ == '__main__':
    main()
