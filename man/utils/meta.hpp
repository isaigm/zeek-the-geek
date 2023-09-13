#pragma once
namespace meta
{
    template <typename T, typename U>
    struct equals
    {
        constexpr static bool value{false};
    };

    template <typename T>
    struct equals<T, T>
    {
        constexpr static bool value{true};
    };
    template <typename T>
    struct type_id
    {
        using type = T;
    };
    template <size_t i, typename... Ts>
    struct nth_type
    {
    };
    template <size_t i, typename T, typename... Ts>
    struct nth_type<i, T, Ts...>
    {
        using type = nth_type<i - 1, Ts...>::type;
    };
    template <typename T, typename... Ts>
    struct nth_type<0, T, Ts...> : type_id<T>
    {
    };

    template <typename T, typename... Ts>
    struct pos_type
    {
        static_assert(sizeof...(Ts) != 0);
    };

    template <typename T, typename... Ts>
    struct pos_type<T, T, Ts...>
    {
        static constexpr size_t value{0};
    };
    template <typename T, typename U, typename... Ts>
    struct pos_type<T, U, Ts...>
    {
        static constexpr size_t value{1 + pos_type<T, Ts...>::value};
    };

    template <typename T, typename U>
    static constexpr bool is_same_v = equals<T, U>::value;

    template <typename... Ts>
    struct TypeList
    {
        consteval static size_t getSize() { return sizeof...(Ts); }
        template <typename T>
        consteval static bool contains()
        {
            return (false || ... || is_same_v<T, Ts>);
        }
        template <typename T>
        consteval static size_t getPos()
        {
            return pos_type<T, Ts...>::value;
        }
    };

    template <typename List>
    struct ComponentTraits
    {
        consteval static int getSize() { return List::getSize(); }

        template <typename T>
        consteval static int getId()
        {
            static_assert(List::template contains<T>());
            return List::template getPos<T>();
        }

        template <typename T>
        consteval static int getMask() { return 1 << getId<T>(); }

        template <typename ...Ts>
        consteval static int getCmpMask()
        {
            return (1 | ... | getMask<Ts>());
        }
    };

    template <template <typename...> class NewType, typename List>
    struct replace
    {
    };
    template <template <typename...> class NewType, typename... Ts>
    struct replace<NewType, TypeList<Ts...>>
    {
        using type = NewType<Ts...>;
    };

    template <template <typename...> class NewType, typename... Ts>
    struct forall_insert_template
    {
    };

    template <template <typename...> class NewType, typename... Ts>
    struct forall_insert_template<NewType, TypeList<Ts...>>
    {
        using type = TypeList<NewType<Ts>...>;
    };
    template <typename T, size_t N>
    struct Pair
    {
        using type = T;
        static constexpr size_t val = N;
    };

} // namespace meta
