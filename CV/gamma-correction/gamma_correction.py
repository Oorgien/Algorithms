import sys, os.path, cv2, numpy as np


def gamma_correction(img: np.ndarray, a: float, b: float) -> np.ndarray:
    # insert your code here
    image = img / 255
    image = a * (image ** b)
    image = (image * 255)
    image[image > 255] = 255
    image[image < 0] = 0
    image = np.around(image).astype(np.uint8)
    # cv2.imshow('image',image)
    # cv2.waitKey(0)
    return image


def main():
    assert len(sys.argv) == 5
    src_path, dst_path = sys.argv[1], sys.argv[2]
    a, b = float(sys.argv[3]), float(sys.argv[4])

    assert os.path.exists(src_path)
    img = cv2.imread(src_path, cv2.IMREAD_GRAYSCALE)
    assert img is not None

    result = gamma_correction(img, a, b)
    cv2.imwrite(dst_path, result)


if __name__ == '__main__':
    main()