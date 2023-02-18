#ifndef UNREAL_CLASSES_UOBJECT_H
#define UNREAL_CLASSES_UOBJECT_H

#include "pch.h"

#include "unreal/structs/fname.h"
#include "unreal/wrappers/prop_traits.h"

namespace unrealsdk::unreal {

#if defined(_MSC_VER) && defined(ARCH_X86)
#pragma pack(push, 0x4)
#endif

class FImplementedInterface;
class UClass;

class UObject {
   public:
    // Prevent actually using as a class, must reinterpret_cast
    UObject() = delete;
    UObject(const UObject&) = delete;
    UObject(UObject&&) = delete;
    UObject& operator=(const UObject&) = delete;
    UObject& operator=(UObject&&) = delete;
    ~UObject() = delete;

    void* vftable;

    // NOLINTBEGIN(readability-identifier-naming)

#if UE4
    int32_t ObjectFlags;
    int32_t InternalIndex;
    UClass* Class;
    FName Name;
    UObject* Outer;
#else
   private:
    void* HashNext;

   public:
    uint64_t ObjectFlags;

   private:
    void* HashOuterNext;
    void* StateFrame;
    class UObject* Linker;
    void* LinkerIndex;
    int ObjectInternalInteger;

   public:
    int InternalIndex;
    UObject* Outer;
    FName Name;
    UClass* Class;

   private:
    UObject* ObjectArchetype;

   public:
#endif

    // NOLINTEND(readability-identifier-naming)

    /**
     * @brief Gets a property on this struct.
     *
     * @tparam T The type of the property.
     * @param name The property's name to lookup.
     * @param prop The property to get.
     * @param idx The fixed array index to get the value at. Defaults to 0.
     * @return The property's new value.
     */
    template <typename T>
    [[nodiscard]] typename PropTraits<T>::Value get(const FName& name, size_t idx = 0) const;
    template <typename T>
    [[nodiscard]] typename PropTraits<T>::Value get(const T* prop, size_t idx = 0) const;

    /**
     * @brief Sets a property on this struct
     *
     * @tparam T The type of the property.
     * @param name The property's name to lookup.
     * @param prop The property to set.
     * @param idx The fixed array index to set the value at. Defaults to 0.
     * @param value The property's value.
     */
    template <typename T>
    void set(const FName& name, typename PropTraits<T>::Value value) {
        this->set<T>(name, 0, value);
    }
    template <typename T>
    void set(const T* prop, typename PropTraits<T>::Value value) {
        this->set<T>(prop, 0, value);
    }
    template <typename T>
    void set(const FName& name, size_t idx, typename PropTraits<T>::Value value);
    template <typename T>
    void set(const T* prop, size_t idx, typename PropTraits<T>::Value value);

    /**
     * @brief Get the object's full path name.
     *
     * @tparam T the string type to get the name as.
     * @return The full path name.
     */
    template <typename T>
    [[nodiscard]] std::basic_string<T> get_path_name(void) const;

    /**
     * @brief Checks if this object is an instance of a class.
     * @note Does not check interfaces, only plain inheritance.
     *
     * @param cls The class to check.
     * @return True if this object is an instance of the given class.
     */
    bool is_instance(const UClass* cls) const;

    /**
     * @brief Checks if this object implements an interface.
     *
     * @param iface The interface to check.
     * @param[out] impl_out If not null, gets set to the interface implementation for this object
     *                      (assuming it's found).
     * @return True if this object implements of the given interface.
     */
    bool is_implementation(const UClass* iface, FImplementedInterface** impl_out = nullptr) const;
};

#if defined(_MSC_VER) && defined(ARCH_X86)
#pragma pack(pop)
#endif

}  // namespace unrealsdk::unreal

#endif /* UNREAL_CLASSES_UOBJECT_H */
