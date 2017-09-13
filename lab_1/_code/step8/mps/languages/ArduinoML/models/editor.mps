<?xml version="1.0" encoding="UTF-8"?>
<model ref="r:a48f37bc-8627-459f-8f77-fc98db464b7c(ArduinoML.editor)">
  <persistence version="9" />
  <languages>
    <use id="18bc6592-03a6-4e29-a83a-7ff23bde13ba" name="jetbrains.mps.lang.editor" version="11" />
    <devkit ref="2677cb18-f558-4e33-bc38-a5139cee06dc(jetbrains.mps.devkit.language-design)" />
  </languages>
  <imports>
    <import index="bt66" ref="r:95dc3936-047b-4df0-883d-ba757a2402dd(ArduinoML.structure)" implicit="true" />
    <import index="tpck" ref="r:00000000-0000-4000-0000-011c89590288(jetbrains.mps.lang.core.structure)" implicit="true" />
  </imports>
  <registry>
    <language id="18bc6592-03a6-4e29-a83a-7ff23bde13ba" name="jetbrains.mps.lang.editor">
      <concept id="1071666914219" name="jetbrains.mps.lang.editor.structure.ConceptEditorDeclaration" flags="ig" index="24kQdi" />
      <concept id="1140524381322" name="jetbrains.mps.lang.editor.structure.CellModel_ListWithRole" flags="ng" index="2czfm3">
        <child id="1140524464360" name="cellLayout" index="2czzBx" />
        <child id="1140524464359" name="emptyCellModel" index="2czzBI" />
      </concept>
      <concept id="1106270549637" name="jetbrains.mps.lang.editor.structure.CellLayout_Horizontal" flags="nn" index="2iRfu4" />
      <concept id="1106270571710" name="jetbrains.mps.lang.editor.structure.CellLayout_Vertical" flags="nn" index="2iRkQZ" />
      <concept id="1237303669825" name="jetbrains.mps.lang.editor.structure.CellLayout_Indent" flags="nn" index="l2Vlx" />
      <concept id="1080736578640" name="jetbrains.mps.lang.editor.structure.BaseEditorComponent" flags="ig" index="2wURMF">
        <child id="1080736633877" name="cellModel" index="2wV5jI" />
      </concept>
      <concept id="1186414536763" name="jetbrains.mps.lang.editor.structure.BooleanStyleSheetItem" flags="ln" index="VOi$J">
        <property id="1186414551515" name="flag" index="VOm3f" />
      </concept>
      <concept id="1186414928363" name="jetbrains.mps.lang.editor.structure.SelectableStyleSheetItem" flags="ln" index="VPM3Z" />
      <concept id="8313721352726366579" name="jetbrains.mps.lang.editor.structure.CellModel_Empty" flags="ng" index="35HoNQ" />
      <concept id="1088013125922" name="jetbrains.mps.lang.editor.structure.CellModel_RefCell" flags="sg" stub="730538219795941030" index="1iCGBv">
        <child id="1088186146602" name="editorComponent" index="1sWHZn" />
      </concept>
      <concept id="1088185857835" name="jetbrains.mps.lang.editor.structure.InlineEditorComponent" flags="ig" index="1sVBvm" />
      <concept id="1139848536355" name="jetbrains.mps.lang.editor.structure.CellModel_WithRole" flags="ng" index="1$h60E">
        <property id="1140017977771" name="readOnly" index="1Intyy" />
        <reference id="1140103550593" name="relationDeclaration" index="1NtTu8" />
      </concept>
      <concept id="1073389446423" name="jetbrains.mps.lang.editor.structure.CellModel_Collection" flags="sn" stub="3013115976261988961" index="3EZMnI">
        <child id="1106270802874" name="cellLayout" index="2iSdaV" />
        <child id="1073389446424" name="childCellModel" index="3EZMnx" />
      </concept>
      <concept id="1073389577006" name="jetbrains.mps.lang.editor.structure.CellModel_Constant" flags="sn" stub="3610246225209162225" index="3F0ifn">
        <property id="1073389577007" name="text" index="3F0ifm" />
      </concept>
      <concept id="1073389658414" name="jetbrains.mps.lang.editor.structure.CellModel_Property" flags="sg" stub="730538219796134133" index="3F0A7n" />
      <concept id="1219418625346" name="jetbrains.mps.lang.editor.structure.IStyleContainer" flags="ng" index="3F0Thp">
        <child id="1219418656006" name="styleItem" index="3F10Kt" />
      </concept>
      <concept id="1073390211982" name="jetbrains.mps.lang.editor.structure.CellModel_RefNodeList" flags="sg" stub="2794558372793454595" index="3F2HdR" />
      <concept id="1198256887712" name="jetbrains.mps.lang.editor.structure.CellModel_Indent" flags="ng" index="3XFhqQ" />
      <concept id="1166049232041" name="jetbrains.mps.lang.editor.structure.AbstractComponent" flags="ng" index="1XWOmA">
        <reference id="1166049300910" name="conceptDeclaration" index="1XX52x" />
      </concept>
    </language>
  </registry>
  <node concept="24kQdi" id="1VAgMjDs1FF">
    <ref role="1XX52x" to="bt66:1VAgMjDrKZ1" resolve="App" />
    <node concept="3EZMnI" id="1VAgMjDs7Yx" role="2wV5jI">
      <node concept="2iRkQZ" id="1VAgMjDs7Yy" role="2iSdaV" />
      <node concept="3EZMnI" id="1VAgMjDs7Y_" role="3EZMnx">
        <node concept="l2Vlx" id="1VAgMjDs7YA" role="2iSdaV" />
        <node concept="VPM3Z" id="1VAgMjDs7YB" role="3F10Kt">
          <property role="VOm3f" value="false" />
        </node>
        <node concept="3F0ifn" id="1VAgMjDs7YF" role="3EZMnx">
          <property role="3F0ifm" value="application" />
        </node>
        <node concept="3F0A7n" id="1VAgMjDs7YK" role="3EZMnx">
          <ref role="1NtTu8" to="tpck:h0TrG11" resolve="name" />
        </node>
      </node>
      <node concept="35HoNQ" id="1VAgMjDs8yl" role="3EZMnx" />
      <node concept="3EZMnI" id="1VAgMjDs7Zl" role="3EZMnx">
        <node concept="VPM3Z" id="1VAgMjDs7Zn" role="3F10Kt">
          <property role="VOm3f" value="false" />
        </node>
        <node concept="3XFhqQ" id="1VAgMjDs7Z_" role="3EZMnx" />
        <node concept="l2Vlx" id="1VAgMjDs7Zq" role="2iSdaV" />
        <node concept="3F2HdR" id="1VAgMjDs7ZT" role="3EZMnx">
          <ref role="1NtTu8" to="bt66:1VAgMjDrKZk" resolve="actuators" />
          <node concept="2iRkQZ" id="1VAgMjDs7ZW" role="2czzBx" />
          <node concept="VPM3Z" id="1VAgMjDs7ZX" role="3F10Kt">
            <property role="VOm3f" value="false" />
          </node>
          <node concept="3F0ifn" id="1VAgMjDs802" role="2czzBI">
            <property role="3F0ifm" value="no actuators defined" />
          </node>
        </node>
      </node>
      <node concept="35HoNQ" id="1VAgMjDs957" role="3EZMnx" />
      <node concept="3EZMnI" id="1VAgMjDs80L" role="3EZMnx">
        <node concept="VPM3Z" id="1VAgMjDs80N" role="3F10Kt">
          <property role="VOm3f" value="false" />
        </node>
        <node concept="l2Vlx" id="1VAgMjDs80Q" role="2iSdaV" />
        <node concept="3XFhqQ" id="1VAgMjDs81k" role="3EZMnx" />
        <node concept="3F2HdR" id="1VAgMjDs81t" role="3EZMnx">
          <ref role="1NtTu8" to="bt66:1VAgMjDrKZi" resolve="states" />
          <node concept="2iRkQZ" id="1VAgMjDs81w" role="2czzBx" />
          <node concept="VPM3Z" id="1VAgMjDs81x" role="3F10Kt">
            <property role="VOm3f" value="false" />
          </node>
          <node concept="3F0ifn" id="1VAgMjDs81A" role="2czzBI">
            <property role="3F0ifm" value="no states defined" />
          </node>
        </node>
      </node>
    </node>
  </node>
  <node concept="24kQdi" id="1VAgMjDs6qC">
    <ref role="1XX52x" to="bt66:1VAgMjDrKZd" resolve="Actuator" />
    <node concept="3EZMnI" id="1VAgMjDs6qE" role="2wV5jI">
      <node concept="3EZMnI" id="1VAgMjDs6qL" role="3EZMnx">
        <node concept="VPM3Z" id="1VAgMjDs6qN" role="3F10Kt">
          <property role="VOm3f" value="false" />
        </node>
        <node concept="3F0ifn" id="1VAgMjDs6qW" role="3EZMnx">
          <property role="3F0ifm" value="actuator:" />
        </node>
        <node concept="3F0A7n" id="1VAgMjDs6r2" role="3EZMnx">
          <ref role="1NtTu8" to="tpck:h0TrG11" resolve="name" />
        </node>
        <node concept="3F0ifn" id="1VAgMjDs6ra" role="3EZMnx">
          <property role="3F0ifm" value="on pin" />
        </node>
        <node concept="3F0A7n" id="1VAgMjDs6rk" role="3EZMnx">
          <ref role="1NtTu8" to="bt66:1VAgMjDrKZg" resolve="pin" />
        </node>
        <node concept="l2Vlx" id="1VAgMjDs6qQ" role="2iSdaV" />
      </node>
      <node concept="2iRfu4" id="1VAgMjDs6qH" role="2iSdaV" />
    </node>
  </node>
  <node concept="24kQdi" id="1VAgMjDs9BR">
    <ref role="1XX52x" to="bt66:1VAgMjDrKZ4" resolve="State" />
    <node concept="3EZMnI" id="1VAgMjDs9BT" role="2wV5jI">
      <node concept="3EZMnI" id="1VAgMjDs9C0" role="3EZMnx">
        <node concept="VPM3Z" id="1VAgMjDs9C2" role="3F10Kt">
          <property role="VOm3f" value="false" />
        </node>
        <node concept="3F0A7n" id="1VAgMjDs9Ce" role="3EZMnx">
          <ref role="1NtTu8" to="tpck:h0TrG11" resolve="name" />
        </node>
        <node concept="3F0ifn" id="1VAgMjDs9Ck" role="3EZMnx">
          <property role="3F0ifm" value=":" />
        </node>
        <node concept="l2Vlx" id="1VAgMjDs9C5" role="2iSdaV" />
        <node concept="3XFhqQ" id="1VAgMjDshPr" role="3EZMnx" />
        <node concept="3XFhqQ" id="1VAgMjDsj1V" role="3EZMnx" />
        <node concept="3XFhqQ" id="1VAgMjDsj2i" role="3EZMnx" />
        <node concept="3F0ifn" id="1VAgMjDshP_" role="3EZMnx">
          <property role="3F0ifm" value="initial:" />
        </node>
        <node concept="3F0A7n" id="1VAgMjDshPS" role="3EZMnx">
          <ref role="1NtTu8" to="bt66:1VAgMjDs1lE" resolve="isInitial" />
        </node>
      </node>
      <node concept="3EZMnI" id="1VAgMjDs9CZ" role="3EZMnx">
        <node concept="VPM3Z" id="1VAgMjDs9D1" role="3F10Kt">
          <property role="VOm3f" value="false" />
        </node>
        <node concept="3XFhqQ" id="1VAgMjDs9Df" role="3EZMnx" />
        <node concept="3F2HdR" id="1VAgMjDs9Dl" role="3EZMnx">
          <ref role="1NtTu8" to="bt66:1VAgMjDrKZp" resolve="actions" />
          <node concept="2iRkQZ" id="1VAgMjDs9Do" role="2czzBx" />
          <node concept="VPM3Z" id="1VAgMjDs9Dp" role="3F10Kt">
            <property role="VOm3f" value="false" />
          </node>
          <node concept="3F0ifn" id="1VAgMjDs9Du" role="2czzBI">
            <property role="3F0ifm" value="no actions defined" />
          </node>
        </node>
        <node concept="l2Vlx" id="1VAgMjDs9D4" role="2iSdaV" />
      </node>
      <node concept="3EZMnI" id="1VAgMjDs9Lv" role="3EZMnx">
        <node concept="VPM3Z" id="1VAgMjDs9Lx" role="3F10Kt">
          <property role="VOm3f" value="false" />
        </node>
        <node concept="l2Vlx" id="1VAgMjDs9L$" role="2iSdaV" />
        <node concept="3XFhqQ" id="1VAgMjDs9M1" role="3EZMnx" />
        <node concept="3F0ifn" id="1VAgMjDs9M6" role="3EZMnx">
          <property role="3F0ifm" value="going to" />
        </node>
        <node concept="1iCGBv" id="1VAgMjDs9Me" role="3EZMnx">
          <ref role="1NtTu8" to="bt66:1VAgMjDrKZt" resolve="next" />
          <node concept="1sVBvm" id="1VAgMjDs9Mg" role="1sWHZn">
            <node concept="3F0A7n" id="1VAgMjDs9Mp" role="2wV5jI">
              <property role="1Intyy" value="true" />
              <ref role="1NtTu8" to="tpck:h0TrG11" resolve="name" />
            </node>
          </node>
        </node>
      </node>
      <node concept="35HoNQ" id="1VAgMjDsc8a" role="3EZMnx" />
      <node concept="2iRkQZ" id="1VAgMjDs9BW" role="2iSdaV" />
    </node>
  </node>
  <node concept="24kQdi" id="1VAgMjDsd3B">
    <ref role="1XX52x" to="bt66:1VAgMjDrKZ7" resolve="Action" />
    <node concept="3EZMnI" id="1VAgMjDsd3D" role="2wV5jI">
      <node concept="1iCGBv" id="1VAgMjDsd3K" role="3EZMnx">
        <ref role="1NtTu8" to="bt66:1VAgMjDrKZy" resolve="target" />
        <node concept="1sVBvm" id="1VAgMjDsd3M" role="1sWHZn">
          <node concept="3F0A7n" id="1VAgMjDsd3T" role="2wV5jI">
            <property role="1Intyy" value="true" />
            <ref role="1NtTu8" to="tpck:h0TrG11" resolve="name" />
          </node>
        </node>
      </node>
      <node concept="3F0ifn" id="1VAgMjDsd41" role="3EZMnx">
        <property role="3F0ifm" value="&lt;=" />
      </node>
      <node concept="3F0A7n" id="1VAgMjDsfy5" role="3EZMnx">
        <ref role="1NtTu8" to="bt66:1VAgMjDrKZw" resolve="signal" />
      </node>
      <node concept="2iRfu4" id="1VAgMjDsd3G" role="2iSdaV" />
    </node>
  </node>
</model>

