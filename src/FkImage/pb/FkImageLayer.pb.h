// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: FkImageLayer.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_FkImageLayer_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_FkImageLayer_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3019000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3019004 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "FkSize.pb.h"
#include "FkRational.pb.h"
#include "FkDoubleVec3.pb.h"
#include "FkFloatVec3.pb.h"
#include "FkPaintPath.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_FkImageLayer_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_FkImageLayer_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_FkImageLayer_2eproto;
namespace com {
namespace alimin {
namespace fk {
namespace pb {
class FkImageLayer;
struct FkImageLayerDefaultTypeInternal;
extern FkImageLayerDefaultTypeInternal _FkImageLayer_default_instance_;
}  // namespace pb
}  // namespace fk
}  // namespace alimin
}  // namespace com
PROTOBUF_NAMESPACE_OPEN
template<> ::com::alimin::fk::pb::FkImageLayer* Arena::CreateMaybeMessage<::com::alimin::fk::pb::FkImageLayer>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace com {
namespace alimin {
namespace fk {
namespace pb {

// ===================================================================

class FkImageLayer final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:com.alimin.fk.pb.FkImageLayer) */ {
 public:
  inline FkImageLayer() : FkImageLayer(nullptr) {}
  ~FkImageLayer() override;
  explicit constexpr FkImageLayer(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  FkImageLayer(const FkImageLayer& from);
  FkImageLayer(FkImageLayer&& from) noexcept
    : FkImageLayer() {
    *this = ::std::move(from);
  }

  inline FkImageLayer& operator=(const FkImageLayer& from) {
    CopyFrom(from);
    return *this;
  }
  inline FkImageLayer& operator=(FkImageLayer&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const FkImageLayer& default_instance() {
    return *internal_default_instance();
  }
  static inline const FkImageLayer* internal_default_instance() {
    return reinterpret_cast<const FkImageLayer*>(
               &_FkImageLayer_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(FkImageLayer& a, FkImageLayer& b) {
    a.Swap(&b);
  }
  inline void Swap(FkImageLayer* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(FkImageLayer* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  FkImageLayer* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<FkImageLayer>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const FkImageLayer& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const FkImageLayer& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(FkImageLayer* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "com.alimin.fk.pb.FkImageLayer";
  }
  protected:
  explicit FkImageLayer(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kPathsFieldNumber = 8,
    kFileFieldNumber = 5,
    kSizeFieldNumber = 1,
    kRotationFieldNumber = 2,
    kScaleFieldNumber = 3,
    kTransFieldNumber = 4,
    kIdFieldNumber = 6,
    kColorFieldNumber = 7,
  };
  // repeated .com.alimin.fk.pb.FkPaintPath paths = 8;
  int paths_size() const;
  private:
  int _internal_paths_size() const;
  public:
  void clear_paths();
  ::com::alimin::fk::pb::FkPaintPath* mutable_paths(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::com::alimin::fk::pb::FkPaintPath >*
      mutable_paths();
  private:
  const ::com::alimin::fk::pb::FkPaintPath& _internal_paths(int index) const;
  ::com::alimin::fk::pb::FkPaintPath* _internal_add_paths();
  public:
  const ::com::alimin::fk::pb::FkPaintPath& paths(int index) const;
  ::com::alimin::fk::pb::FkPaintPath* add_paths();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::com::alimin::fk::pb::FkPaintPath >&
      paths() const;

  // string file = 5;
  void clear_file();
  const std::string& file() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_file(ArgT0&& arg0, ArgT... args);
  std::string* mutable_file();
  PROTOBUF_NODISCARD std::string* release_file();
  void set_allocated_file(std::string* file);
  private:
  const std::string& _internal_file() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_file(const std::string& value);
  std::string* _internal_mutable_file();
  public:

  // .com.alimin.fk.pb.FkSize size = 1;
  bool has_size() const;
  private:
  bool _internal_has_size() const;
  public:
  void clear_size();
  const ::com::alimin::fk::pb::FkSize& size() const;
  PROTOBUF_NODISCARD ::com::alimin::fk::pb::FkSize* release_size();
  ::com::alimin::fk::pb::FkSize* mutable_size();
  void set_allocated_size(::com::alimin::fk::pb::FkSize* size);
  private:
  const ::com::alimin::fk::pb::FkSize& _internal_size() const;
  ::com::alimin::fk::pb::FkSize* _internal_mutable_size();
  public:
  void unsafe_arena_set_allocated_size(
      ::com::alimin::fk::pb::FkSize* size);
  ::com::alimin::fk::pb::FkSize* unsafe_arena_release_size();

  // .com.alimin.fk.pb.FkRational rotation = 2;
  bool has_rotation() const;
  private:
  bool _internal_has_rotation() const;
  public:
  void clear_rotation();
  const ::com::alimin::fk::pb::FkRational& rotation() const;
  PROTOBUF_NODISCARD ::com::alimin::fk::pb::FkRational* release_rotation();
  ::com::alimin::fk::pb::FkRational* mutable_rotation();
  void set_allocated_rotation(::com::alimin::fk::pb::FkRational* rotation);
  private:
  const ::com::alimin::fk::pb::FkRational& _internal_rotation() const;
  ::com::alimin::fk::pb::FkRational* _internal_mutable_rotation();
  public:
  void unsafe_arena_set_allocated_rotation(
      ::com::alimin::fk::pb::FkRational* rotation);
  ::com::alimin::fk::pb::FkRational* unsafe_arena_release_rotation();

  // .com.alimin.fk.pb.FkFloatVec3 scale = 3;
  bool has_scale() const;
  private:
  bool _internal_has_scale() const;
  public:
  void clear_scale();
  const ::com::alimin::fk::pb::FkFloatVec3& scale() const;
  PROTOBUF_NODISCARD ::com::alimin::fk::pb::FkFloatVec3* release_scale();
  ::com::alimin::fk::pb::FkFloatVec3* mutable_scale();
  void set_allocated_scale(::com::alimin::fk::pb::FkFloatVec3* scale);
  private:
  const ::com::alimin::fk::pb::FkFloatVec3& _internal_scale() const;
  ::com::alimin::fk::pb::FkFloatVec3* _internal_mutable_scale();
  public:
  void unsafe_arena_set_allocated_scale(
      ::com::alimin::fk::pb::FkFloatVec3* scale);
  ::com::alimin::fk::pb::FkFloatVec3* unsafe_arena_release_scale();

  // .com.alimin.fk.pb.FkDoubleVec3 trans = 4;
  bool has_trans() const;
  private:
  bool _internal_has_trans() const;
  public:
  void clear_trans();
  const ::com::alimin::fk::pb::FkDoubleVec3& trans() const;
  PROTOBUF_NODISCARD ::com::alimin::fk::pb::FkDoubleVec3* release_trans();
  ::com::alimin::fk::pb::FkDoubleVec3* mutable_trans();
  void set_allocated_trans(::com::alimin::fk::pb::FkDoubleVec3* trans);
  private:
  const ::com::alimin::fk::pb::FkDoubleVec3& _internal_trans() const;
  ::com::alimin::fk::pb::FkDoubleVec3* _internal_mutable_trans();
  public:
  void unsafe_arena_set_allocated_trans(
      ::com::alimin::fk::pb::FkDoubleVec3* trans);
  ::com::alimin::fk::pb::FkDoubleVec3* unsafe_arena_release_trans();

  // int32 id = 6;
  void clear_id();
  int32_t id() const;
  void set_id(int32_t value);
  private:
  int32_t _internal_id() const;
  void _internal_set_id(int32_t value);
  public:

  // int32 color = 7;
  void clear_color();
  int32_t color() const;
  void set_color(int32_t value);
  private:
  int32_t _internal_color() const;
  void _internal_set_color(int32_t value);
  public:

  // @@protoc_insertion_point(class_scope:com.alimin.fk.pb.FkImageLayer)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::com::alimin::fk::pb::FkPaintPath > paths_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr file_;
  ::com::alimin::fk::pb::FkSize* size_;
  ::com::alimin::fk::pb::FkRational* rotation_;
  ::com::alimin::fk::pb::FkFloatVec3* scale_;
  ::com::alimin::fk::pb::FkDoubleVec3* trans_;
  int32_t id_;
  int32_t color_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_FkImageLayer_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// FkImageLayer

// .com.alimin.fk.pb.FkSize size = 1;
inline bool FkImageLayer::_internal_has_size() const {
  return this != internal_default_instance() && size_ != nullptr;
}
inline bool FkImageLayer::has_size() const {
  return _internal_has_size();
}
inline const ::com::alimin::fk::pb::FkSize& FkImageLayer::_internal_size() const {
  const ::com::alimin::fk::pb::FkSize* p = size_;
  return p != nullptr ? *p : reinterpret_cast<const ::com::alimin::fk::pb::FkSize&>(
      ::com::alimin::fk::pb::_FkSize_default_instance_);
}
inline const ::com::alimin::fk::pb::FkSize& FkImageLayer::size() const {
  // @@protoc_insertion_point(field_get:com.alimin.fk.pb.FkImageLayer.size)
  return _internal_size();
}
inline void FkImageLayer::unsafe_arena_set_allocated_size(
    ::com::alimin::fk::pb::FkSize* size) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(size_);
  }
  size_ = size;
  if (size) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:com.alimin.fk.pb.FkImageLayer.size)
}
inline ::com::alimin::fk::pb::FkSize* FkImageLayer::release_size() {
  
  ::com::alimin::fk::pb::FkSize* temp = size_;
  size_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old =  reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(temp);
  temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  if (GetArenaForAllocation() == nullptr) { delete old; }
#else  // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return temp;
}
inline ::com::alimin::fk::pb::FkSize* FkImageLayer::unsafe_arena_release_size() {
  // @@protoc_insertion_point(field_release:com.alimin.fk.pb.FkImageLayer.size)
  
  ::com::alimin::fk::pb::FkSize* temp = size_;
  size_ = nullptr;
  return temp;
}
inline ::com::alimin::fk::pb::FkSize* FkImageLayer::_internal_mutable_size() {
  
  if (size_ == nullptr) {
    auto* p = CreateMaybeMessage<::com::alimin::fk::pb::FkSize>(GetArenaForAllocation());
    size_ = p;
  }
  return size_;
}
inline ::com::alimin::fk::pb::FkSize* FkImageLayer::mutable_size() {
  ::com::alimin::fk::pb::FkSize* _msg = _internal_mutable_size();
  // @@protoc_insertion_point(field_mutable:com.alimin.fk.pb.FkImageLayer.size)
  return _msg;
}
inline void FkImageLayer::set_allocated_size(::com::alimin::fk::pb::FkSize* size) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(size_);
  }
  if (size) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper<
            ::PROTOBUF_NAMESPACE_ID::MessageLite>::GetOwningArena(
                reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(size));
    if (message_arena != submessage_arena) {
      size = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, size, submessage_arena);
    }
    
  } else {
    
  }
  size_ = size;
  // @@protoc_insertion_point(field_set_allocated:com.alimin.fk.pb.FkImageLayer.size)
}

// .com.alimin.fk.pb.FkRational rotation = 2;
inline bool FkImageLayer::_internal_has_rotation() const {
  return this != internal_default_instance() && rotation_ != nullptr;
}
inline bool FkImageLayer::has_rotation() const {
  return _internal_has_rotation();
}
inline const ::com::alimin::fk::pb::FkRational& FkImageLayer::_internal_rotation() const {
  const ::com::alimin::fk::pb::FkRational* p = rotation_;
  return p != nullptr ? *p : reinterpret_cast<const ::com::alimin::fk::pb::FkRational&>(
      ::com::alimin::fk::pb::_FkRational_default_instance_);
}
inline const ::com::alimin::fk::pb::FkRational& FkImageLayer::rotation() const {
  // @@protoc_insertion_point(field_get:com.alimin.fk.pb.FkImageLayer.rotation)
  return _internal_rotation();
}
inline void FkImageLayer::unsafe_arena_set_allocated_rotation(
    ::com::alimin::fk::pb::FkRational* rotation) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(rotation_);
  }
  rotation_ = rotation;
  if (rotation) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:com.alimin.fk.pb.FkImageLayer.rotation)
}
inline ::com::alimin::fk::pb::FkRational* FkImageLayer::release_rotation() {
  
  ::com::alimin::fk::pb::FkRational* temp = rotation_;
  rotation_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old =  reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(temp);
  temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  if (GetArenaForAllocation() == nullptr) { delete old; }
#else  // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return temp;
}
inline ::com::alimin::fk::pb::FkRational* FkImageLayer::unsafe_arena_release_rotation() {
  // @@protoc_insertion_point(field_release:com.alimin.fk.pb.FkImageLayer.rotation)
  
  ::com::alimin::fk::pb::FkRational* temp = rotation_;
  rotation_ = nullptr;
  return temp;
}
inline ::com::alimin::fk::pb::FkRational* FkImageLayer::_internal_mutable_rotation() {
  
  if (rotation_ == nullptr) {
    auto* p = CreateMaybeMessage<::com::alimin::fk::pb::FkRational>(GetArenaForAllocation());
    rotation_ = p;
  }
  return rotation_;
}
inline ::com::alimin::fk::pb::FkRational* FkImageLayer::mutable_rotation() {
  ::com::alimin::fk::pb::FkRational* _msg = _internal_mutable_rotation();
  // @@protoc_insertion_point(field_mutable:com.alimin.fk.pb.FkImageLayer.rotation)
  return _msg;
}
inline void FkImageLayer::set_allocated_rotation(::com::alimin::fk::pb::FkRational* rotation) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(rotation_);
  }
  if (rotation) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper<
            ::PROTOBUF_NAMESPACE_ID::MessageLite>::GetOwningArena(
                reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(rotation));
    if (message_arena != submessage_arena) {
      rotation = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, rotation, submessage_arena);
    }
    
  } else {
    
  }
  rotation_ = rotation;
  // @@protoc_insertion_point(field_set_allocated:com.alimin.fk.pb.FkImageLayer.rotation)
}

// .com.alimin.fk.pb.FkFloatVec3 scale = 3;
inline bool FkImageLayer::_internal_has_scale() const {
  return this != internal_default_instance() && scale_ != nullptr;
}
inline bool FkImageLayer::has_scale() const {
  return _internal_has_scale();
}
inline const ::com::alimin::fk::pb::FkFloatVec3& FkImageLayer::_internal_scale() const {
  const ::com::alimin::fk::pb::FkFloatVec3* p = scale_;
  return p != nullptr ? *p : reinterpret_cast<const ::com::alimin::fk::pb::FkFloatVec3&>(
      ::com::alimin::fk::pb::_FkFloatVec3_default_instance_);
}
inline const ::com::alimin::fk::pb::FkFloatVec3& FkImageLayer::scale() const {
  // @@protoc_insertion_point(field_get:com.alimin.fk.pb.FkImageLayer.scale)
  return _internal_scale();
}
inline void FkImageLayer::unsafe_arena_set_allocated_scale(
    ::com::alimin::fk::pb::FkFloatVec3* scale) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(scale_);
  }
  scale_ = scale;
  if (scale) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:com.alimin.fk.pb.FkImageLayer.scale)
}
inline ::com::alimin::fk::pb::FkFloatVec3* FkImageLayer::release_scale() {
  
  ::com::alimin::fk::pb::FkFloatVec3* temp = scale_;
  scale_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old =  reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(temp);
  temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  if (GetArenaForAllocation() == nullptr) { delete old; }
#else  // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return temp;
}
inline ::com::alimin::fk::pb::FkFloatVec3* FkImageLayer::unsafe_arena_release_scale() {
  // @@protoc_insertion_point(field_release:com.alimin.fk.pb.FkImageLayer.scale)
  
  ::com::alimin::fk::pb::FkFloatVec3* temp = scale_;
  scale_ = nullptr;
  return temp;
}
inline ::com::alimin::fk::pb::FkFloatVec3* FkImageLayer::_internal_mutable_scale() {
  
  if (scale_ == nullptr) {
    auto* p = CreateMaybeMessage<::com::alimin::fk::pb::FkFloatVec3>(GetArenaForAllocation());
    scale_ = p;
  }
  return scale_;
}
inline ::com::alimin::fk::pb::FkFloatVec3* FkImageLayer::mutable_scale() {
  ::com::alimin::fk::pb::FkFloatVec3* _msg = _internal_mutable_scale();
  // @@protoc_insertion_point(field_mutable:com.alimin.fk.pb.FkImageLayer.scale)
  return _msg;
}
inline void FkImageLayer::set_allocated_scale(::com::alimin::fk::pb::FkFloatVec3* scale) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(scale_);
  }
  if (scale) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper<
            ::PROTOBUF_NAMESPACE_ID::MessageLite>::GetOwningArena(
                reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(scale));
    if (message_arena != submessage_arena) {
      scale = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, scale, submessage_arena);
    }
    
  } else {
    
  }
  scale_ = scale;
  // @@protoc_insertion_point(field_set_allocated:com.alimin.fk.pb.FkImageLayer.scale)
}

// .com.alimin.fk.pb.FkDoubleVec3 trans = 4;
inline bool FkImageLayer::_internal_has_trans() const {
  return this != internal_default_instance() && trans_ != nullptr;
}
inline bool FkImageLayer::has_trans() const {
  return _internal_has_trans();
}
inline const ::com::alimin::fk::pb::FkDoubleVec3& FkImageLayer::_internal_trans() const {
  const ::com::alimin::fk::pb::FkDoubleVec3* p = trans_;
  return p != nullptr ? *p : reinterpret_cast<const ::com::alimin::fk::pb::FkDoubleVec3&>(
      ::com::alimin::fk::pb::_FkDoubleVec3_default_instance_);
}
inline const ::com::alimin::fk::pb::FkDoubleVec3& FkImageLayer::trans() const {
  // @@protoc_insertion_point(field_get:com.alimin.fk.pb.FkImageLayer.trans)
  return _internal_trans();
}
inline void FkImageLayer::unsafe_arena_set_allocated_trans(
    ::com::alimin::fk::pb::FkDoubleVec3* trans) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(trans_);
  }
  trans_ = trans;
  if (trans) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:com.alimin.fk.pb.FkImageLayer.trans)
}
inline ::com::alimin::fk::pb::FkDoubleVec3* FkImageLayer::release_trans() {
  
  ::com::alimin::fk::pb::FkDoubleVec3* temp = trans_;
  trans_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old =  reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(temp);
  temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  if (GetArenaForAllocation() == nullptr) { delete old; }
#else  // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return temp;
}
inline ::com::alimin::fk::pb::FkDoubleVec3* FkImageLayer::unsafe_arena_release_trans() {
  // @@protoc_insertion_point(field_release:com.alimin.fk.pb.FkImageLayer.trans)
  
  ::com::alimin::fk::pb::FkDoubleVec3* temp = trans_;
  trans_ = nullptr;
  return temp;
}
inline ::com::alimin::fk::pb::FkDoubleVec3* FkImageLayer::_internal_mutable_trans() {
  
  if (trans_ == nullptr) {
    auto* p = CreateMaybeMessage<::com::alimin::fk::pb::FkDoubleVec3>(GetArenaForAllocation());
    trans_ = p;
  }
  return trans_;
}
inline ::com::alimin::fk::pb::FkDoubleVec3* FkImageLayer::mutable_trans() {
  ::com::alimin::fk::pb::FkDoubleVec3* _msg = _internal_mutable_trans();
  // @@protoc_insertion_point(field_mutable:com.alimin.fk.pb.FkImageLayer.trans)
  return _msg;
}
inline void FkImageLayer::set_allocated_trans(::com::alimin::fk::pb::FkDoubleVec3* trans) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(trans_);
  }
  if (trans) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper<
            ::PROTOBUF_NAMESPACE_ID::MessageLite>::GetOwningArena(
                reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(trans));
    if (message_arena != submessage_arena) {
      trans = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, trans, submessage_arena);
    }
    
  } else {
    
  }
  trans_ = trans;
  // @@protoc_insertion_point(field_set_allocated:com.alimin.fk.pb.FkImageLayer.trans)
}

// string file = 5;
inline void FkImageLayer::clear_file() {
  file_.ClearToEmpty();
}
inline const std::string& FkImageLayer::file() const {
  // @@protoc_insertion_point(field_get:com.alimin.fk.pb.FkImageLayer.file)
  return _internal_file();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void FkImageLayer::set_file(ArgT0&& arg0, ArgT... args) {
 
 file_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:com.alimin.fk.pb.FkImageLayer.file)
}
inline std::string* FkImageLayer::mutable_file() {
  std::string* _s = _internal_mutable_file();
  // @@protoc_insertion_point(field_mutable:com.alimin.fk.pb.FkImageLayer.file)
  return _s;
}
inline const std::string& FkImageLayer::_internal_file() const {
  return file_.Get();
}
inline void FkImageLayer::_internal_set_file(const std::string& value) {
  
  file_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* FkImageLayer::_internal_mutable_file() {
  
  return file_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* FkImageLayer::release_file() {
  // @@protoc_insertion_point(field_release:com.alimin.fk.pb.FkImageLayer.file)
  return file_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void FkImageLayer::set_allocated_file(std::string* file) {
  if (file != nullptr) {
    
  } else {
    
  }
  file_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), file,
      GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (file_.IsDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited())) {
    file_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:com.alimin.fk.pb.FkImageLayer.file)
}

// int32 id = 6;
inline void FkImageLayer::clear_id() {
  id_ = 0;
}
inline int32_t FkImageLayer::_internal_id() const {
  return id_;
}
inline int32_t FkImageLayer::id() const {
  // @@protoc_insertion_point(field_get:com.alimin.fk.pb.FkImageLayer.id)
  return _internal_id();
}
inline void FkImageLayer::_internal_set_id(int32_t value) {
  
  id_ = value;
}
inline void FkImageLayer::set_id(int32_t value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:com.alimin.fk.pb.FkImageLayer.id)
}

// int32 color = 7;
inline void FkImageLayer::clear_color() {
  color_ = 0;
}
inline int32_t FkImageLayer::_internal_color() const {
  return color_;
}
inline int32_t FkImageLayer::color() const {
  // @@protoc_insertion_point(field_get:com.alimin.fk.pb.FkImageLayer.color)
  return _internal_color();
}
inline void FkImageLayer::_internal_set_color(int32_t value) {
  
  color_ = value;
}
inline void FkImageLayer::set_color(int32_t value) {
  _internal_set_color(value);
  // @@protoc_insertion_point(field_set:com.alimin.fk.pb.FkImageLayer.color)
}

// repeated .com.alimin.fk.pb.FkPaintPath paths = 8;
inline int FkImageLayer::_internal_paths_size() const {
  return paths_.size();
}
inline int FkImageLayer::paths_size() const {
  return _internal_paths_size();
}
inline ::com::alimin::fk::pb::FkPaintPath* FkImageLayer::mutable_paths(int index) {
  // @@protoc_insertion_point(field_mutable:com.alimin.fk.pb.FkImageLayer.paths)
  return paths_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::com::alimin::fk::pb::FkPaintPath >*
FkImageLayer::mutable_paths() {
  // @@protoc_insertion_point(field_mutable_list:com.alimin.fk.pb.FkImageLayer.paths)
  return &paths_;
}
inline const ::com::alimin::fk::pb::FkPaintPath& FkImageLayer::_internal_paths(int index) const {
  return paths_.Get(index);
}
inline const ::com::alimin::fk::pb::FkPaintPath& FkImageLayer::paths(int index) const {
  // @@protoc_insertion_point(field_get:com.alimin.fk.pb.FkImageLayer.paths)
  return _internal_paths(index);
}
inline ::com::alimin::fk::pb::FkPaintPath* FkImageLayer::_internal_add_paths() {
  return paths_.Add();
}
inline ::com::alimin::fk::pb::FkPaintPath* FkImageLayer::add_paths() {
  ::com::alimin::fk::pb::FkPaintPath* _add = _internal_add_paths();
  // @@protoc_insertion_point(field_add:com.alimin.fk.pb.FkImageLayer.paths)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::com::alimin::fk::pb::FkPaintPath >&
FkImageLayer::paths() const {
  // @@protoc_insertion_point(field_list:com.alimin.fk.pb.FkImageLayer.paths)
  return paths_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace pb
}  // namespace fk
}  // namespace alimin
}  // namespace com

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_FkImageLayer_2eproto
