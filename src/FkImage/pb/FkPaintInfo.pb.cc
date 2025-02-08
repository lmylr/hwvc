// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: FkPaintInfo.proto

#include "FkPaintInfo.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace com {
namespace alimin {
namespace fk {
namespace pb {
constexpr FkPaintInfo::FkPaintInfo(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : strokewidth_(0)
  , color_(0){}
struct FkPaintInfoDefaultTypeInternal {
  constexpr FkPaintInfoDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~FkPaintInfoDefaultTypeInternal() {}
  union {
    FkPaintInfo _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT FkPaintInfoDefaultTypeInternal _FkPaintInfo_default_instance_;
}  // namespace pb
}  // namespace fk
}  // namespace alimin
}  // namespace com
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_FkPaintInfo_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_FkPaintInfo_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_FkPaintInfo_2eproto = nullptr;

const uint32_t TableStruct_FkPaintInfo_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::com::alimin::fk::pb::FkPaintInfo, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::com::alimin::fk::pb::FkPaintInfo, strokewidth_),
  PROTOBUF_FIELD_OFFSET(::com::alimin::fk::pb::FkPaintInfo, color_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::com::alimin::fk::pb::FkPaintInfo)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::com::alimin::fk::pb::_FkPaintInfo_default_instance_),
};

const char descriptor_table_protodef_FkPaintInfo_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\021FkPaintInfo.proto\022\020com.alimin.fk.pb\"1\n"
  "\013FkPaintInfo\022\023\n\013strokeWidth\030\001 \001(\005\022\r\n\005col"
  "or\030\002 \001(\005b\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_FkPaintInfo_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_FkPaintInfo_2eproto = {
  false, false, 96, descriptor_table_protodef_FkPaintInfo_2eproto, "FkPaintInfo.proto", 
  &descriptor_table_FkPaintInfo_2eproto_once, nullptr, 0, 1,
  schemas, file_default_instances, TableStruct_FkPaintInfo_2eproto::offsets,
  file_level_metadata_FkPaintInfo_2eproto, file_level_enum_descriptors_FkPaintInfo_2eproto, file_level_service_descriptors_FkPaintInfo_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_FkPaintInfo_2eproto_getter() {
  return &descriptor_table_FkPaintInfo_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_FkPaintInfo_2eproto(&descriptor_table_FkPaintInfo_2eproto);
namespace com {
namespace alimin {
namespace fk {
namespace pb {

// ===================================================================

class FkPaintInfo::_Internal {
 public:
};

FkPaintInfo::FkPaintInfo(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:com.alimin.fk.pb.FkPaintInfo)
}
FkPaintInfo::FkPaintInfo(const FkPaintInfo& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&strokewidth_, &from.strokewidth_,
    static_cast<size_t>(reinterpret_cast<char*>(&color_) -
    reinterpret_cast<char*>(&strokewidth_)) + sizeof(color_));
  // @@protoc_insertion_point(copy_constructor:com.alimin.fk.pb.FkPaintInfo)
}

inline void FkPaintInfo::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&strokewidth_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&color_) -
    reinterpret_cast<char*>(&strokewidth_)) + sizeof(color_));
}

FkPaintInfo::~FkPaintInfo() {
  // @@protoc_insertion_point(destructor:com.alimin.fk.pb.FkPaintInfo)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void FkPaintInfo::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void FkPaintInfo::ArenaDtor(void* object) {
  FkPaintInfo* _this = reinterpret_cast< FkPaintInfo* >(object);
  (void)_this;
}
void FkPaintInfo::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void FkPaintInfo::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void FkPaintInfo::Clear() {
// @@protoc_insertion_point(message_clear_start:com.alimin.fk.pb.FkPaintInfo)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&strokewidth_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&color_) -
      reinterpret_cast<char*>(&strokewidth_)) + sizeof(color_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* FkPaintInfo::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 strokeWidth = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          strokewidth_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 color = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          color_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* FkPaintInfo::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:com.alimin.fk.pb.FkPaintInfo)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 strokeWidth = 1;
  if (this->_internal_strokewidth() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_strokewidth(), target);
  }

  // int32 color = 2;
  if (this->_internal_color() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(2, this->_internal_color(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:com.alimin.fk.pb.FkPaintInfo)
  return target;
}

size_t FkPaintInfo::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:com.alimin.fk.pb.FkPaintInfo)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int32 strokeWidth = 1;
  if (this->_internal_strokewidth() != 0) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32SizePlusOne(this->_internal_strokewidth());
  }

  // int32 color = 2;
  if (this->_internal_color() != 0) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32SizePlusOne(this->_internal_color());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData FkPaintInfo::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    FkPaintInfo::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*FkPaintInfo::GetClassData() const { return &_class_data_; }

void FkPaintInfo::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<FkPaintInfo *>(to)->MergeFrom(
      static_cast<const FkPaintInfo &>(from));
}


void FkPaintInfo::MergeFrom(const FkPaintInfo& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:com.alimin.fk.pb.FkPaintInfo)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_strokewidth() != 0) {
    _internal_set_strokewidth(from._internal_strokewidth());
  }
  if (from._internal_color() != 0) {
    _internal_set_color(from._internal_color());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void FkPaintInfo::CopyFrom(const FkPaintInfo& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:com.alimin.fk.pb.FkPaintInfo)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool FkPaintInfo::IsInitialized() const {
  return true;
}

void FkPaintInfo::InternalSwap(FkPaintInfo* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(FkPaintInfo, color_)
      + sizeof(FkPaintInfo::color_)
      - PROTOBUF_FIELD_OFFSET(FkPaintInfo, strokewidth_)>(
          reinterpret_cast<char*>(&strokewidth_),
          reinterpret_cast<char*>(&other->strokewidth_));
}

::PROTOBUF_NAMESPACE_ID::Metadata FkPaintInfo::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_FkPaintInfo_2eproto_getter, &descriptor_table_FkPaintInfo_2eproto_once,
      file_level_metadata_FkPaintInfo_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace pb
}  // namespace fk
}  // namespace alimin
}  // namespace com
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::com::alimin::fk::pb::FkPaintInfo* Arena::CreateMaybeMessage< ::com::alimin::fk::pb::FkPaintInfo >(Arena* arena) {
  return Arena::CreateMessageInternal< ::com::alimin::fk::pb::FkPaintInfo >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
