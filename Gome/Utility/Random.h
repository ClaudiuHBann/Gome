#pragma once

template <typename Type>
concept Arithmetical = is_arithmetic_v<Type>;

class Random
{
  public:
    Random() : mGenerator(mSeeder())
    {
    }

    template <Arithmetical Type,
              typename UniformDistribution =
                  conditional_t<is_integral_v<Type>, uniform_int_distribution<Type>, uniform_real_distribution<Type>>>
    inline auto Get(const Type min = numeric_limits<Type>::min(), const Type max = numeric_limits<Type>::max())
    {
        return UniformDistribution(min, max)(mGenerator);
    }

  private:
    random_device mSeeder;
    mt19937 mGenerator;
};
