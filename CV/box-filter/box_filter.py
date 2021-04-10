import sys, os.path, cv2, numpy as np


def box_filter(img: np.ndarray, w: int, h: int) -> np.ndarray:
    """
    Сложность алгоритма О(N) т.к. для построения интегрального изображения требуется
    выполнить О(N) операций, и для построения сглаженного изображения требуется О(N)
    операций, суммарная сложность О(N), где N - кол-во пикселей на изображении

    """

    int_image = np.zeros(img.shape, dtype=np.uint64)
    for y in range(img.shape[0]):
        for x in range(img.shape[1]):
            top = int_image[y-1, x] if y-1 >= 0 else 0
            left = int_image[y, x-1] if x-1 >= 0 else 0
            diag = int_image[y-1,x-1] if (x-1 >= 0 and y-1 >= 0) else 0
            int_image[y,x] = int(top) + int(left) - int(diag) + img[y, x]

    blured = np.zeros(img.shape)

    """
    Если фильтр по одной из осей нечетного размера,
    то в одну перераспределяем расстояния до точек прямоугольника
    относительно текущей точки
    """
    if w % 2 != 0:
        w1 = w//2
        w2 = w//2 + 1
    else:
        w1 = w2 = w//2

    if h % 2 != 0:
        h1 = h//2
        h2 = h//2 + 1
    else:
        h1 = h2 = h//2


    for y in range(img.shape[0]):
        for x in range(img.shape[1]):
            A = int_image[max(0 , y-h1), max(0, x - w1)]
            B = int_image[max(0 , y-h1), min(img.shape[1]-1,x + w2)]
            C = int_image[min(img.shape[0]-1,y + h2), max(0, x - w1)]
            D = int_image[min(img.shape[0]-1,y + h2), min(img.shape[1]-1,x + w2)]
            Sum = A + D - B - C
            # print (Sum/(h * w))
            blured[min(img.shape[0]-1,y),min(img.shape[1]-1,x)] = int(Sum/(h * w))

    return blured
def main():
    assert len(sys.argv) == 5
    src_path, dst_path = sys.argv[1], sys.argv[2]
    w, h = int(sys.argv[3]), int(sys.argv[4])
    assert w > 0
    assert h > 0

    assert os.path.exists(src_path)
    img = cv2.imread(src_path, cv2.IMREAD_GRAYSCALE)
    assert img is not None

    result = box_filter(img, w, h)
    cv2.imwrite(dst_path, result)

    # test = cv2.blur(img, (w,h))
    # cv2.imwrite('test.png', test)

if __name__ == '__main__':
    main()
