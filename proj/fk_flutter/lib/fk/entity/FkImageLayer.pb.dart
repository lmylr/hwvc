//
//  Generated code. Do not modify.
//  source: FkImageLayer.proto
//
// @dart = 2.12

// ignore_for_file: annotate_overrides, camel_case_types, comment_references
// ignore_for_file: constant_identifier_names, library_prefixes
// ignore_for_file: non_constant_identifier_names, prefer_final_fields
// ignore_for_file: unnecessary_import, unnecessary_this, unused_import

import 'dart:core' as $core;

import 'package:protobuf/protobuf.dart' as $pb;

import 'FkDoubleVec3.pb.dart' as $0;
import 'FkFloatVec3.pb.dart' as $3;
import 'FkPaintPath.pb.dart' as $4;
import 'FkRational.pb.dart' as $2;
import 'FkSize.pb.dart' as $1;

class FkImageLayer extends $pb.GeneratedMessage {
  factory FkImageLayer({
    $1.FkSize? size,
    $2.FkRational? rotation,
    $3.FkFloatVec3? scale,
    $0.FkDoubleVec3? trans,
    $core.String? file,
    $core.int? id,
    $core.int? color,
    $core.Iterable<$4.FkPaintPath>? paths,
  }) {
    final $result = create();
    if (size != null) {
      $result.size = size;
    }
    if (rotation != null) {
      $result.rotation = rotation;
    }
    if (scale != null) {
      $result.scale = scale;
    }
    if (trans != null) {
      $result.trans = trans;
    }
    if (file != null) {
      $result.file = file;
    }
    if (id != null) {
      $result.id = id;
    }
    if (color != null) {
      $result.color = color;
    }
    if (paths != null) {
      $result.paths.addAll(paths);
    }
    return $result;
  }
  FkImageLayer._() : super();
  factory FkImageLayer.fromBuffer($core.List<$core.int> i, [$pb.ExtensionRegistry r = $pb.ExtensionRegistry.EMPTY]) => create()..mergeFromBuffer(i, r);
  factory FkImageLayer.fromJson($core.String i, [$pb.ExtensionRegistry r = $pb.ExtensionRegistry.EMPTY]) => create()..mergeFromJson(i, r);

  static final $pb.BuilderInfo _i = $pb.BuilderInfo(_omitMessageNames ? '' : 'FkImageLayer', package: const $pb.PackageName(_omitMessageNames ? '' : 'com.alimin.fk.pb'), createEmptyInstance: create)
    ..aOM<$1.FkSize>(1, _omitFieldNames ? '' : 'size', subBuilder: $1.FkSize.create)
    ..aOM<$2.FkRational>(2, _omitFieldNames ? '' : 'rotation', subBuilder: $2.FkRational.create)
    ..aOM<$3.FkFloatVec3>(3, _omitFieldNames ? '' : 'scale', subBuilder: $3.FkFloatVec3.create)
    ..aOM<$0.FkDoubleVec3>(4, _omitFieldNames ? '' : 'trans', subBuilder: $0.FkDoubleVec3.create)
    ..aOS(5, _omitFieldNames ? '' : 'file')
    ..a<$core.int>(6, _omitFieldNames ? '' : 'id', $pb.PbFieldType.O3)
    ..a<$core.int>(7, _omitFieldNames ? '' : 'color', $pb.PbFieldType.O3)
    ..pc<$4.FkPaintPath>(8, _omitFieldNames ? '' : 'paths', $pb.PbFieldType.PM, subBuilder: $4.FkPaintPath.create)
    ..hasRequiredFields = false
  ;

  @$core.Deprecated(
  'Using this can add significant overhead to your binary. '
  'Use [GeneratedMessageGenericExtensions.deepCopy] instead. '
  'Will be removed in next major version')
  FkImageLayer clone() => FkImageLayer()..mergeFromMessage(this);
  @$core.Deprecated(
  'Using this can add significant overhead to your binary. '
  'Use [GeneratedMessageGenericExtensions.rebuild] instead. '
  'Will be removed in next major version')
  FkImageLayer copyWith(void Function(FkImageLayer) updates) => super.copyWith((message) => updates(message as FkImageLayer)) as FkImageLayer;

  $pb.BuilderInfo get info_ => _i;

  @$core.pragma('dart2js:noInline')
  static FkImageLayer create() => FkImageLayer._();
  FkImageLayer createEmptyInstance() => create();
  static $pb.PbList<FkImageLayer> createRepeated() => $pb.PbList<FkImageLayer>();
  @$core.pragma('dart2js:noInline')
  static FkImageLayer getDefault() => _defaultInstance ??= $pb.GeneratedMessage.$_defaultFor<FkImageLayer>(create);
  static FkImageLayer? _defaultInstance;

  /// reserved 2, 15, 9 to 11;
  /// reserved "foo", "bar";
  @$pb.TagNumber(1)
  $1.FkSize get size => $_getN(0);
  @$pb.TagNumber(1)
  set size($1.FkSize v) { setField(1, v); }
  @$pb.TagNumber(1)
  $core.bool hasSize() => $_has(0);
  @$pb.TagNumber(1)
  void clearSize() => clearField(1);
  @$pb.TagNumber(1)
  $1.FkSize ensureSize() => $_ensure(0);

  @$pb.TagNumber(2)
  $2.FkRational get rotation => $_getN(1);
  @$pb.TagNumber(2)
  set rotation($2.FkRational v) { setField(2, v); }
  @$pb.TagNumber(2)
  $core.bool hasRotation() => $_has(1);
  @$pb.TagNumber(2)
  void clearRotation() => clearField(2);
  @$pb.TagNumber(2)
  $2.FkRational ensureRotation() => $_ensure(1);

  @$pb.TagNumber(3)
  $3.FkFloatVec3 get scale => $_getN(2);
  @$pb.TagNumber(3)
  set scale($3.FkFloatVec3 v) { setField(3, v); }
  @$pb.TagNumber(3)
  $core.bool hasScale() => $_has(2);
  @$pb.TagNumber(3)
  void clearScale() => clearField(3);
  @$pb.TagNumber(3)
  $3.FkFloatVec3 ensureScale() => $_ensure(2);

  @$pb.TagNumber(4)
  $0.FkDoubleVec3 get trans => $_getN(3);
  @$pb.TagNumber(4)
  set trans($0.FkDoubleVec3 v) { setField(4, v); }
  @$pb.TagNumber(4)
  $core.bool hasTrans() => $_has(3);
  @$pb.TagNumber(4)
  void clearTrans() => clearField(4);
  @$pb.TagNumber(4)
  $0.FkDoubleVec3 ensureTrans() => $_ensure(3);

  @$pb.TagNumber(5)
  $core.String get file => $_getSZ(4);
  @$pb.TagNumber(5)
  set file($core.String v) { $_setString(4, v); }
  @$pb.TagNumber(5)
  $core.bool hasFile() => $_has(4);
  @$pb.TagNumber(5)
  void clearFile() => clearField(5);

  @$pb.TagNumber(6)
  $core.int get id => $_getIZ(5);
  @$pb.TagNumber(6)
  set id($core.int v) { $_setSignedInt32(5, v); }
  @$pb.TagNumber(6)
  $core.bool hasId() => $_has(5);
  @$pb.TagNumber(6)
  void clearId() => clearField(6);

  @$pb.TagNumber(7)
  $core.int get color => $_getIZ(6);
  @$pb.TagNumber(7)
  set color($core.int v) { $_setSignedInt32(6, v); }
  @$pb.TagNumber(7)
  $core.bool hasColor() => $_has(6);
  @$pb.TagNumber(7)
  void clearColor() => clearField(7);

  @$pb.TagNumber(8)
  $core.List<$4.FkPaintPath> get paths => $_getList(7);
}


const _omitFieldNames = $core.bool.fromEnvironment('protobuf.omit_field_names');
const _omitMessageNames = $core.bool.fromEnvironment('protobuf.omit_message_names');
