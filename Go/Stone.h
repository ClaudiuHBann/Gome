#pragma once

class Stone
{
  public:
    Stone(const size_t x, const size_t y);

    pair<size_t, size_t> GetPosition() const;
    void SetPosition(const size_t x, const size_t y);

    bool operator==(const Stone &stone);

  private:
    size_t mX{};
    size_t mY{};
};
