#pragma once

class Random
{
  public:
    Random() : mGenerator(mSeeder())
    {
    }

    template <typename Type = int>
    auto GetInt(const Type min = numeric_limits<Type>::min(), const Type max = numeric_limits<Type>::max())
    {
        return uniform_int_distribution<Type>(min, max)(mGenerator);
    }

    template <typename Type = float>
    auto GetReal(const Type min = numeric_limits<Type>::min(), const Type max = numeric_limits<Type>::max())
    {
        return uniform_real_distribution<Type>(min, max)(mGenerator);
    }

    template <typename Type>
    auto Get(const Type min = numeric_limits<Type>::min(), const Type max = numeric_limits<Type>::max())
    {
        if constexpr (is_integral_v<Type>)
        {
            return GetInt(min, max);
        }
        else if constexpr (is_floating_point_v<Type>)
        {
            return GetReal(min, max);
        }
        else
        {
            return {};
        }
    }

    template <typename Type>
    auto GetVector(const size_t size, const Type min = numeric_limits<Type>::min(),
                   const Type max = numeric_limits<Type>::max())
    {
        return views::iota(0U, size) | views::transform([=](auto _) { return Get(min, max); });
    }

  private:
    random_device mSeeder;
    mt19937 mGenerator;
};
