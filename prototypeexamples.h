#include <catch2/catch_test_macros.hpp>
#include <memory>

class Type
{
public:
    virtual ~Type() = default;
    virtual std::unique_ptr<Type> Clone() = 0;
};

class TypeA final : public Type
{
public:
    std::unique_ptr<Type> Clone() override { return std::make_unique<TypeA>(*this); }
    void SetValue(const int32_t value) { m_Value = value; }
    int32_t GetValue() const { return m_Value; }
private:
    int32_t m_Value{0};
};

class TypeB final : public Type
{
public:
    std::unique_ptr<Type> Clone() override { return std::make_unique<TypeB>(*this); }
    void SetValue(const float_t value) { m_Value = value; }
    float_t GetValue() const { return m_Value; }
private:
    float_t m_Value{0.0f};
};

TEST_CASE("Prototype - Unit Tests")
{
    std::unique_ptr<TypeA> typeA{std::make_unique<TypeA>()};
    std::unique_ptr<TypeB> typeB{std::make_unique<TypeB>()};
    REQUIRE(typeA->GetValue() == 0);
    REQUIRE(typeB->GetValue() == 0.0f);

    typeA->SetValue(1);
    typeB->SetValue(2.0f);
    REQUIRE(typeA->GetValue() == 1);
    REQUIRE(typeB->GetValue() == 2.0f);

    std::unique_ptr<Type> typeAClone{typeA->Clone()};
    REQUIRE(typeAClone != typeA);
    REQUIRE(static_cast<const TypeA*>(typeAClone.get())->GetValue() == typeA->GetValue());

    typeA->SetValue(2);
    REQUIRE(static_cast<const TypeA*>(typeAClone.get())->GetValue() != typeA->GetValue());
}
