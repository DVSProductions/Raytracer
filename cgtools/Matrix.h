#pragma once
#include "ISerializable.h"
#include "direction.h"
#include <memory>
#include <cinttypes>
#define __atm3(v,o,s) o(((v*2)+0)) s o(((v*2)+1))
#define __atm2(v,o,s) __atm3(((v*2)+0),o,s) s __atm3(((v*2)+1),o,s)
#define __atm1(v,o,s) __atm2(((v*2)+0),o,s) s __atm2(((v*2)+1),o,s)
#define __applyToMatrix(operation, separator) __atm1(0,operation,separator) separator __atm1(1,operation,separator)
namespace cgtools {
	class matrix : public ISerializable {
		double values[16] = { 0 };
		public: 
			matrix(double v1, double v2, double v3, double v4, double v5, double v6, double v7, double v8, double v9, double v10, double v11, double v12, double v13, double v14, double v15, double v16) noexcept;
			matrix()noexcept;
		matrix(direction b0, direction b1, direction b2)noexcept;
		matrix(direction b0, direction b1, direction b2,point b3)noexcept;
		static matrix createScaler(vector v) noexcept;
		static matrix createScaler(double x, double y, double z) noexcept;
		static matrix createRotation(direction caxis, double angle) noexcept;
		static matrix createRotationX(double angle) noexcept;
		static matrix createRotationY(double angle) noexcept;
		static matrix createRotationZ(double angle) noexcept;
		static matrix createTranslation(vector t) noexcept;
		static matrix createTranslation(double x, double y, double z) noexcept;
		matrix operator*(matrix m) const noexcept;
		matrix operator*=(matrix m)noexcept;
		point operator*(point p)const noexcept;
		direction operator*(direction d)const noexcept;
		/// <summary>
		/// transpose Matrix
		/// </summary>
		/// <returns>transposed matrix</returns>
		matrix operator~()const noexcept ;
		/// <summary>
		/// Invert matrix
		/// </summary>
		/// <returns>Inverted matrix</returns>
		matrix operator!()const;
		bool operator==(const matrix& p) const noexcept;
		std::string serialize()const override;
		void load(std::string serialized)override;
		size_t size()const override;
		std::string toString() const;
	};
}

