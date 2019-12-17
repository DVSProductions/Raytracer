#define _USE_MATH_DEFINES
#include <cmath>
#include "Matrix.h"

#if _WIN64
#else
#include <stdexcept>
#endif
#define get(c,r) values[4*c+r]
#define set(c,r,v) get(c,r)=v
#define ___serializeMatrix(idx) std::to_string(values[idx])+"|"
#define ___loadMatrix(idx) f_chars(ret[idx], values[idx])
#define ___copyMatrix(idx) values[idx]=r.values[idx]
#define ___setDet(idx) __dst[idx]=det 
#define ___isEqual(idx) values[idx] == p.values[idx]
#define ___isMat(idx) values[idx]
#define ___th2(x,y) ret.set(x, y, get(y, x))
#define ___th1(v) ___th2(v,0);___th2(v,1);___th2(v,2);___th2(v,3)
#define ___tildehelper() ___th1(0);___th1(1);___th1(2);___th1(3)
#define __mat values
#define __dst ret.values
#define _comma ,
namespace cgtools {
	matrix::matrix(
		double v0,
		double v1,
		double v2,
		double v3,
		double v4,
		double v5,
		double v6,
		double v7,
		double v8,
		double v9,
		double v10,
		double v11,
		double v12,
		double v13,
		double v14,
		double v15
		) noexcept {
		values[0] = v0;
		values[1] = v1;
		values[2] = v2;
		values[3] = v3;
		values[4] = v4;
		values[5] = v5;
		values[6] = v6;
		values[7] = v7;
		values[8] = v8;
		values[9] = v9;
		values[10] = v10;
		values[11] = v11;
		values[12] = v12;
		values[13] = v13;
		values[14] = v14;
		values[15] = v15;
	}
	matrix::matrix() noexcept {
		set(0, 0, 1.0);
		set(1, 1, 1.0);
		set(2, 2, 1.0);
		set(3, 3, 1.0);
	}

	matrix matrix::createScaler(vector v) noexcept {
		matrix m;
		m.set(0, 0, v.x);
		m.set(1, 1, v.y);
		m.set(2, 2, v.z);
		return m;
	}

	matrix matrix::createScaler(double x, double y, double z) noexcept {
		matrix m;
		m.set(0, 0, x);
		m.set(1, 1, y);
		m.set(2, 2, z);
		return m;
	}
	matrix matrix::createRotation(direction caxis, double angle) noexcept {
		matrix m;
		const double rad = (angle / 180.0f) * (M_PI);
		const double cosa = cos(rad);
		const double sina = sin(rad);
		const double l = sqrt(caxis.x * caxis.x + caxis.y * caxis.y + caxis.z * caxis.z);
		const double rx = caxis.x / l;
		const double ry = caxis.y / l;
		const double rz = caxis.z / l;
		const double icosa = 1 - cosa;

		m.set(0, 0, icosa * rx * rx + cosa);
		m.set(0, 1, icosa * rx * ry + rz * sina);
		m.set(0, 2, icosa * rx * rz - ry * sina);

		m.set(1, 0, icosa * rx * ry - rz * sina);
		m.set(1, 1, icosa * ry * ry + cosa);
		m.set(1, 2, icosa * ry * rz + rx * sina);

		m.set(2, 0, icosa * rx * rz + ry * sina);
		m.set(2, 1, icosa * ry * rz - rx * sina);
		m.set(2, 2, icosa * rz * rz + cosa);
		return m;
	}
	matrix matrix::createTranslation(vector t) noexcept {
		matrix m;
		m.set(3, 0, t.x);
		m.set(3, 1, t.y);
		m.set(3, 2, t.z);
		return m;
	}
	matrix::matrix(direction b0, direction b1, direction b2)noexcept {
		set(0, 0, b0.x);
		set(0, 1, b1.x);
		set(0, 2, b2.x);
		set(1, 0, b0.y);
		set(1, 1, b1.y);
		set(1, 2, b2.y);
		set(2, 0, b0.z);
		set(2, 1, b1.z);
		set(2, 2, b2.z);
	}

	matrix::matrix(direction b0, direction b1, direction b2, point b3)noexcept {
		set(0, 0, b0.x);
		set(0, 1, b1.x);
		set(0, 2, b2.x);
		set(0, 3, b3.x);
		set(1, 0, b0.y);
		set(1, 1, b1.y);
		set(1, 2, b2.y);
		set(1, 3, b3.y);
		set(2, 0, b0.z);
		set(2, 1, b1.z);
		set(2, 2, b2.z);
		set(2, 3, b3.z);
	}
	matrix matrix::operator*(matrix m) const noexcept {
		matrix ret;
		ret.set(0, 0, get(0, 0) * m.get(0, 0) + get(1, 0) * m.get(0, 1) + get(2, 0) * m.get(0, 2) + get(3, 0) * m.get(0, 3));
		ret.set(0, 1, get(0, 1) * m.get(0, 0) + get(1, 1) * m.get(0, 1) + get(2, 1) * m.get(0, 2) + get(3, 1) * m.get(0, 3));
		ret.set(0, 2, get(0, 2) * m.get(0, 0) + get(1, 2) * m.get(0, 1) + get(2, 2) * m.get(0, 2) + get(3, 2) * m.get(0, 3));
		ret.set(0, 3, get(0, 3) * m.get(0, 0) + get(1, 3) * m.get(0, 1) + get(2, 3) * m.get(0, 2) + get(3, 3) * m.get(0, 3));
		ret.set(1, 0, get(0, 0) * m.get(1, 0) + get(1, 0) * m.get(1, 1) + get(2, 0) * m.get(1, 2) + get(3, 0) * m.get(1, 3));
		ret.set(1, 1, get(0, 1) * m.get(1, 0) + get(1, 1) * m.get(1, 1) + get(2, 1) * m.get(1, 2) + get(3, 1) * m.get(1, 3));
		ret.set(1, 2, get(0, 2) * m.get(1, 0) + get(1, 2) * m.get(1, 1) + get(2, 2) * m.get(1, 2) + get(3, 2) * m.get(1, 3));
		ret.set(1, 3, get(0, 3) * m.get(1, 0) + get(1, 3) * m.get(1, 1) + get(2, 3) * m.get(1, 2) + get(3, 3) * m.get(1, 3));
		ret.set(2, 0, get(0, 0) * m.get(2, 0) + get(1, 0) * m.get(2, 1) + get(2, 0) * m.get(2, 2) + get(3, 0) * m.get(2, 3));
		ret.set(2, 1, get(0, 1) * m.get(2, 0) + get(1, 1) * m.get(2, 1) + get(2, 1) * m.get(2, 2) + get(3, 1) * m.get(2, 3));
		ret.set(2, 2, get(0, 2) * m.get(2, 0) + get(1, 2) * m.get(2, 1) + get(2, 2) * m.get(2, 2) + get(3, 2) * m.get(2, 3));
		ret.set(2, 3, get(0, 3) * m.get(2, 0) + get(1, 3) * m.get(2, 1) + get(2, 3) * m.get(2, 2) + get(3, 3) * m.get(2, 3));
		ret.set(3, 0, get(0, 0) * m.get(3, 0) + get(1, 0) * m.get(3, 1) + get(2, 0) * m.get(3, 2) + get(3, 0) * m.get(3, 3));
		ret.set(3, 1, get(0, 1) * m.get(3, 0) + get(1, 1) * m.get(3, 1) + get(2, 1) * m.get(3, 2) + get(3, 1) * m.get(3, 3));
		ret.set(3, 2, get(0, 2) * m.get(3, 0) + get(1, 2) * m.get(3, 1) + get(2, 2) * m.get(3, 2) + get(3, 2) * m.get(3, 3));
		ret.set(3, 3, get(0, 3) * m.get(3, 0) + get(1, 3) * m.get(3, 1) + get(2, 3) * m.get(3, 2) + get(3, 3) * m.get(3, 3));
		return ret;
	}

	matrix matrix::operator*=(matrix m) noexcept {
		const auto r = (*this) * m;
		__applyToMatrix(___copyMatrix, ;);
		return *this;
	}

	point matrix::operator*(point p) const noexcept {
		return point(
			get(0, 0) * p.x + get(1, 0) * p.y + get(2, 0) * p.z + get(3, 0),
			get(0, 1) * p.x + get(1, 1) * p.y + get(2, 1) * p.z + get(3, 1),
			get(0, 2) * p.x + get(1, 2) * p.y + get(2, 2) * p.z + get(3, 2));
	}

	direction matrix::operator*(direction d) const noexcept {
		return direction(
			get(0, 0) * d.x + get(1, 0) * d.y + get(2, 0) * d.z,
			get(0, 1) * d.x + get(1, 1) * d.y + get(2, 1) * d.z,
			get(0, 2) * d.x + get(1, 2) * d.y + get(2, 2) * d.z);
	}

	matrix matrix::operator~() const noexcept {
		matrix ret;
		___tildehelper();
		return ret;
	}

	/// <summary>
	/// invert
	/// </summary>
	/// <returns>inverted Matrix</returns>
	matrix matrix::operator!()const {
		matrix ret;
		const double src[16] = { __applyToMatrix(___isMat, _comma) };

		/* calculate pairs for first 8 elements (cofactors) */
		double tmp[12] = {
			src[15] * src[10],
			src[14] * src[11],
			src[15] * src[9] ,
			src[13] * src[11],
			src[14] * src[9] ,
			src[13] * src[10],
			src[15] * src[8] ,
			src[12] * src[11],
			src[14] * src[8] ,
			src[12] * src[10],
			src[13] * src[8] ,
			src[12] * src[9]
		};

		/* calculate first 8 elements (cofactors) */
		__dst[0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7]
			/*		    */ - tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
		__dst[1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7]
			/*		    */ - tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
		__dst[2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7]
			/*		    */ - tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
		__dst[3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6]
			/*		    */ - tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
		__dst[4] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3]
			/*		    */ - tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
		__dst[5] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3]
			/*		    */ - tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
		__dst[6] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3]
			/*		    */ - tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
		__dst[7] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2]
			/*		    */ - tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];

		/* calculate pairs for second 8 elements (cofactors) */
		tmp[0] = src[2] * src[7];
		tmp[1] = src[3] * src[6];
		tmp[2] = src[1] * src[7];
		tmp[3] = src[3] * src[5];
		tmp[4] = src[1] * src[6];
		tmp[5] = src[2] * src[5];
		tmp[6] = src[0] * src[7];
		tmp[7] = src[3] * src[4];
		tmp[8] = src[0] * src[6];
		tmp[9] = src[2] * src[4];
		tmp[10] = src[0] * src[5];
		tmp[11] = src[1] * src[4];
		/* calculate second 8 elements (cofactors) */
		__dst[8] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15]
			/*		    */ - tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
		__dst[9] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15]
			/*		    */ - tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
		__dst[10] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15]
			/*		    */ - tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
		__dst[11] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14]
			/*		    */ - tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
		__dst[12] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9]
			/*		    */ - tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
		__dst[13] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10]
			/*		    */ - tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
		__dst[14] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8]
			/*		    */ - tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
		__dst[15] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9]
			/*		    */ - tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];
		/* calculate determinant */
		double det = src[0] * __dst[0] + src[1] * __dst[1] + src[2] * __dst[2] + src[3] * __dst[3];
		if (det == 0.0)
#if _WIN64
			throw std::exception("singular matrix is not invertible");
#else
			throw std::runtime_error("singular matrix is not invertible");
#endif
		det = 1 / det;
		__applyToMatrix(___setDet, ;);
		return ret;
	}
	/// <summary>
	/// Equals
	/// </summary>
	/// <param name="p"></param>
	/// <returns></returns>
	bool matrix::operator==(const matrix& p)const noexcept {
		return __applyToMatrix(___isEqual, &&);
	}

	std::string matrix::serialize() const {
		return __applyToMatrix(___serializeMatrix, +);
	}

	void matrix::load(std::string serialized) {
		auto ret = Serializable::split(serialized);
		__applyToMatrix(___loadMatrix, ;);
	}

	size_t matrix::size() const {
		return sizeof(matrix);
	}
	std::string matrix::toString() const {
		std::string s = "";
		for (int r = 0; r < 4; r++) {
			s += "( ";
			for (int c = 0; c < 4; c++)
				s += std::to_string(get(c, r)) + " ";
			s += ")\n";
		}
		return s;
	}
}