#pragma once

template <typename Type>
concept Arithmetical = is_arithmetic_v<Type>;

/**
 * @brief A class for generating random numbers
 */
class Random
{
  public:
    /**
     * @brief Constructor
     */
    Random() : mGenerator(mSeeder())
    {
    }

    /**
     * @brief Creates a random number within a inclusive domain
     * @tparam UniformDistribution SFINAE for the uniform distributions (used internally)
     * @tparam Type integer or decimal
     * @param min the min number from the domain (inclusive)
     * @param max the max number from the domain (inclusive)
     * @return the random number
     */
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
