#ifndef UNREALSDK_UNREAL_WRAPPERS_GOBJECTS_H
#define UNREALSDK_UNREAL_WRAPPERS_GOBJECTS_H

#include "unrealsdk/pch.h"

#if UNREALSDK_FLAVOUR == UNREALSDK_FLAVOUR_OAK || UNREALSDK_FLAVOUR == UNREALSDK_FLAVOUR_OAK2
#include "unrealsdk/unreal/structs/gobjects.h"
#elif UNREALSDK_FLAVOUR == UNREALSDK_FLAVOUR_WILLOW
#include "unrealsdk/unreal/structs/tarray.h"
#else
#error Unknown SDK flavour
#endif

namespace unrealsdk::unreal {

struct FWeakObjectPtr;
class UObject;

class GObjects {
   public:
#if UNREALSDK_FLAVOUR == UNREALSDK_FLAVOUR_OAK || UNREALSDK_FLAVOUR == UNREALSDK_FLAVOUR_OAK2
    using internal_type = FUObjectArray*;
#elif UNREALSDK_FLAVOUR == UNREALSDK_FLAVOUR_WILLOW
    using internal_type = TArray<UObject*>*;
#else
#error Unknown SDK flavour
#endif

   private:
    internal_type internal;

   public:
    struct Iterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = UObject*;
        using pointer = UObject**;
        using reference = UObject*;

       private:
        const GObjects* gobjects;
        size_t idx;

       public:
        Iterator(void);
        Iterator(const GObjects& gobjects, size_t idx);

        reference operator*() const;

        Iterator& operator++();
        Iterator operator++(int);

        bool operator==(const Iterator& rhs) const;
        bool operator!=(const Iterator& rhs) const;
    };

    /**
     * @brief Construct a new GObjects wrapper.
     *
     * @param internal A pointer to the internal GObjects structure.
     */
    GObjects(void);
    GObjects(internal_type internal);

    /**
     * @brief Get the size of the array.
     *
     * @return The size of the array.
     */
    [[nodiscard]] size_t size(void) const;

    /**
     * @brief Get an object from the array, with bounds checking.
     *
     * @param idx The index to get.
     * @return The item at that index.
     */
    [[nodiscard]] UObject* obj_at(size_t idx) const;

    /**
     * @brief Gets an iterator to the start of GObjects.
     *
     * @return The iterator.
     */
    [[nodiscard]] Iterator begin(void) const;

    /**
     * @brief Gets an iterator to the end of GObjects.
     *
     * @return The iterator.
     */
    [[nodiscard]] static Iterator end(void);

    /**
     * @brief Get the object behind a weak object pointer (or null if it's invalid).
     *
     * @param ptr The weak object pointer.
     * @return The object behind the pointer.
     */
    [[nodiscard]] UObject* get_weak_object(const FWeakObjectPtr* ptr) const;

    /**
     * @brief Sets the object behind a weak object pointer.
     *
     * @param ptr The weak object pointer.
     * @param obj The object to set.
     */
    void set_weak_object(FWeakObjectPtr* ptr, const UObject* obj) const;
};

}  // namespace unrealsdk::unreal

#endif /* UNREALSDK_UNREAL_WRAPPERS_GOBJECTS_H */
