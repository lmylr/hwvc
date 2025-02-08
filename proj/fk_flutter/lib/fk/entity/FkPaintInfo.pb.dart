//
//  Generated code. Do not modify.
//  source: FkPaintInfo.proto
//
// @dart = 2.12

// ignore_for_file: annotate_overrides, camel_case_types, comment_references
// ignore_for_file: constant_identifier_names, library_prefixes
// ignore_for_file: non_constant_identifier_names, prefer_final_fields
// ignore_for_file: unnecessary_import, unnecessary_this, unused_import

import 'dart:core' as $core;

import 'package:protobuf/protobuf.dart' as $pb;

class FkPaintInfo extends $pb.GeneratedMessage {
  factory FkPaintInfo({
    $core.int? strokeWidth,
    $core.int? color,
  }) {
    final $result = create();
    if (strokeWidth != null) {
      $result.strokeWidth = strokeWidth;
    }
    if (color != null) {
      $result.color = color;
    }
    return $result;
  }
  FkPaintInfo._() : super();
  factory FkPaintInfo.fromBuffer($core.List<$core.int> i, [$pb.ExtensionRegistry r = $pb.ExtensionRegistry.EMPTY]) => create()..mergeFromBuffer(i, r);
  factory FkPaintInfo.fromJson($core.String i, [$pb.ExtensionRegistry r = $pb.ExtensionRegistry.EMPTY]) => create()..mergeFromJson(i, r);

  static final $pb.BuilderInfo _i = $pb.BuilderInfo(_omitMessageNames ? '' : 'FkPaintInfo', package: const $pb.PackageName(_omitMessageNames ? '' : 'com.alimin.fk.pb'), createEmptyInstance: create)
    ..a<$core.int>(1, _omitFieldNames ? '' : 'strokeWidth', $pb.PbFieldType.O3, protoName: 'strokeWidth')
    ..a<$core.int>(2, _omitFieldNames ? '' : 'color', $pb.PbFieldType.O3)
    ..hasRequiredFields = false
  ;

  @$core.Deprecated(
  'Using this can add significant overhead to your binary. '
  'Use [GeneratedMessageGenericExtensions.deepCopy] instead. '
  'Will be removed in next major version')
  FkPaintInfo clone() => FkPaintInfo()..mergeFromMessage(this);
  @$core.Deprecated(
  'Using this can add significant overhead to your binary. '
  'Use [GeneratedMessageGenericExtensions.rebuild] instead. '
  'Will be removed in next major version')
  FkPaintInfo copyWith(void Function(FkPaintInfo) updates) => super.copyWith((message) => updates(message as FkPaintInfo)) as FkPaintInfo;

  $pb.BuilderInfo get info_ => _i;

  @$core.pragma('dart2js:noInline')
  static FkPaintInfo create() => FkPaintInfo._();
  FkPaintInfo createEmptyInstance() => create();
  static $pb.PbList<FkPaintInfo> createRepeated() => $pb.PbList<FkPaintInfo>();
  @$core.pragma('dart2js:noInline')
  static FkPaintInfo getDefault() => _defaultInstance ??= $pb.GeneratedMessage.$_defaultFor<FkPaintInfo>(create);
  static FkPaintInfo? _defaultInstance;

  @$pb.TagNumber(1)
  $core.int get strokeWidth => $_getIZ(0);
  @$pb.TagNumber(1)
  set strokeWidth($core.int v) { $_setSignedInt32(0, v); }
  @$pb.TagNumber(1)
  $core.bool hasStrokeWidth() => $_has(0);
  @$pb.TagNumber(1)
  void clearStrokeWidth() => clearField(1);

  @$pb.TagNumber(2)
  $core.int get color => $_getIZ(1);
  @$pb.TagNumber(2)
  set color($core.int v) { $_setSignedInt32(1, v); }
  @$pb.TagNumber(2)
  $core.bool hasColor() => $_has(1);
  @$pb.TagNumber(2)
  void clearColor() => clearField(2);
}


const _omitFieldNames = $core.bool.fromEnvironment('protobuf.omit_field_names');
const _omitMessageNames = $core.bool.fromEnvironment('protobuf.omit_message_names');
