#pragma once
#include <inttypes.h>
class randfast {
	uint_fast64_t internal_next;
	uint64_t custom_lcg()noexcept;
	double generate()noexcept;
	double MI = 0,MA = 0;
public:
	randfast(uint64_t seed)noexcept;
	randfast(uint64_t seed, double min, double max) noexcept;
	/// <summary>
	/// Generates unbiased output between  0 (exclusive) and 1 (exclusive)
	/// </summary>
	/// <returns></returns>
	double operator() ()noexcept;
	/// <summary>
	/// Generates unbiased output betwen min (exclusive) and max (exclusive)
	/// </summary>
	double operator()(double min, double max)noexcept;
	/// <summary>
	/// Generates unbiased output betwen min (exclusive) and max (exclusive)
	/// <para>
	/// Set values with <see cref="setOffset"/>. this reduces calculations
	/// </para>
	/// </summary>
	double apply()noexcept;
	/// <summary>
	/// Sets values for Apply function
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	void setOffset(double min, double max)noexcept;
};

