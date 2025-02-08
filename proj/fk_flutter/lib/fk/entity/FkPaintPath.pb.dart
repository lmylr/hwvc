//
//  Generated code. Do not modify.
//  source: FkPaintPath.proto
//
// @dart = 2.12

// ignore_for_file: annotate_overrides, camel_case_types, comment_references
// ignore_for_file: constant_identifier_names, library_prefixes
// ignore_for_file: non_constant_identifier_names, prefer_final_fields
// ignore_for_file: unnecessary_import, unnecessary_this, unused_import

import 'dart:core' as $core;

import 'package:protobuf/protobuf.dart' as $pb;

import 'FkDoubleVec3.pb.dart' as $0;

class FkPaintPath extends $pb.GeneratedMessage {
  factory FkPaintPath({
    $core.int? type,
    $core.int? color,
    $core.Iterable<$0.FkDoubleVec3>? points,
  }) {
    final $result = create();
    if (type != null) {
      $result.type = type;
    }
    if (color != null) {
      $result.color = color;
    }
    if (points != null) {
      $result.points.addAll(points);
    }
    return $result;
  }
  FkPaintPath._() : super();
  factory FkPaintPath.fromBuffer($core.List<$core.int> i, [$pb.ExtensionRegistry r = $pb.ExtensionRegistry.EMPTY]) => create()..mergeFromBuffer(i, r);
  factory FkPaintPath.fromJson($core.String i, [$pb.ExtensionRegistry r = $pb.ExtensionRegistry.EMPTY]) => create()..mergeFromJson(i, r);

  static final $pb.BuilderInfo _i = $pb.BuilderInfo(_omitMessageNames ? '' : 'FkPaintPath', package: const $pb.PackageName(_omitMessageNames ? '' : 'com.alimin.fk.pb'), createEmptyInstance: create)
    ..a<$core.int>(1, _omitFieldNames ? '' : 'type', $pb.PbFieldType.O3)
    ..a<$core.int>(2, _omitFieldNames ? '' : 'color', $pb.PbFieldType.O3)
    ..pc<$0.FkDoubleVec3>(3, _omitFieldNames ? '' : 'points', $pb.PbFieldType.PM, subBuilder: $0.FkDoubleVec3.create)
    ..hasRequiredFields = false
  ;

  @$core.Deprecated(
  'Using this can add significant overhead to your binary. '
  'Use [GeneratedMessageGenericExtensions.deepCopy] instead. '
  'Will be removed in next major version')
  FkPaintPath clone() => FkPaintPath()..mergeFromMessage(this);
  @$core.Deprecated(
  'Using this can add significant overhead to your binary. '
  'Use [GeneratedMessageGenericExtensions.rebuild] instead. '
  'Will be removed in next major version')
  FkPaintPath copyWith(void Function(FkPaintPath) updates) => super.copyWith((message) => updates(message as FkPaintPath)) as FkPaintPath;

  $pb.BuilderInfo get info_ => _i;

  @$core.pragma('dart2js:noInline')
  static FkPaintPath create() => FkPaintPath._();
  FkPaintPath createEmptyInstance() => create();
  static $pb.PbList<FkPaintPath> createRepeated() => $pb.PbList<FkPaintPath>();
  @$core.pragma('dart2js:noInline')
  static FkPaintPath getDefault() => _defaultInstance ??= $pb.GeneratedMessage.$_defaultFor<FkPaintPath>(create);
  static FkPaintPath? _defaultInstance;

  @$pb.TagNumber(1)
  $core.int get type => $_getIZ(0);
  @$pb.TagNumber(1)
  set type($core.int v) { $_setSignedInt32(0, v); }
  @$pb.TagNumber(1)
  $core.bool hasType() => $_has(0);
  @$pb.TagNumber(1)
  void clearType() => clearField(1);

  @$pb.TagNumber(2)
  $core.int get color => $_getIZ(1);
  @$pb.TagNumber(2)
  set color($core.int v) { $_setSignedInt32(1, v); }
  @$pb.TagNumber(2)
  $core.bool hasColor() => $_has(1);
  @$pb.TagNumber(2)
  void clearColor() => clearField(2);

  @$pb.TagNumber(3)
  $core.List<$0.FkDoubleVec3> get points => $_getList(2);
}


const _omitFieldNames = $core.bool.fromEnvironment('protobuf.omit_field_names');
const _omitMessageNames = $core.bool.fromEnvironment('protobuf.omit_message_names');
