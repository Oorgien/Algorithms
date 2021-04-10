import pytest, numpy as np
from gamma_correction import gamma_correction


class TestGammaCorrection:
    params_1pix = np.load('params_1pix.npy', allow_pickle=True)
    params_4pix = np.load('params_4pix.npy', allow_pickle=True)

    @pytest.mark.parametrize("value, a, b, expected", params_1pix)
    def test_1pix(self, value, a, b, expected):
        result = gamma_correction(np.array(value, ndmin=2, dtype=np.uint8), a, b)
        assert result.dtype == np.uint8
        assert result.shape == (1, 1)
        assert result[0, 0] == expected

    @pytest.mark.parametrize("a, b, expected", params_4pix)
    def test_4pix(self, a, b, expected):
        img = np.array([[51, 102], [153, 204]], dtype=np.uint8)
        result = gamma_correction(img, a, b)
        assert result.dtype == np.uint8
        assert result.shape == (2, 2)
        assert (result == expected).all()
