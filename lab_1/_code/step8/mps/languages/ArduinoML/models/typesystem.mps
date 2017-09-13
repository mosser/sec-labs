<?xml version="1.0" encoding="UTF-8"?>
<model ref="r:20dd5926-3136-454b-8579-6e02ae2c6fe9(ArduinoML.typesystem)">
  <persistence version="9" />
  <languages>
    <use id="7a5dda62-9140-4668-ab76-d5ed1746f2b2" name="jetbrains.mps.lang.typesystem" version="1" />
    <devkit ref="00000000-0000-4000-0000-1de82b3a4936(jetbrains.mps.devkit.aspect.typesystem)" />
  </languages>
  <imports>
    <import index="bt66" ref="r:95dc3936-047b-4df0-883d-ba757a2402dd(ArduinoML.structure)" implicit="true" />
    <import index="tpck" ref="r:00000000-0000-4000-0000-011c89590288(jetbrains.mps.lang.core.structure)" implicit="true" />
  </imports>
  <registry>
    <language id="f3061a53-9226-4cc5-a443-f952ceaf5816" name="jetbrains.mps.baseLanguage">
      <concept id="4836112446988635817" name="jetbrains.mps.baseLanguage.structure.UndefinedType" flags="in" index="2jxLKc" />
      <concept id="1197027756228" name="jetbrains.mps.baseLanguage.structure.DotExpression" flags="nn" index="2OqwBi">
        <child id="1197027771414" name="operand" index="2Oq$k0" />
        <child id="1197027833540" name="operation" index="2OqNvi" />
      </concept>
      <concept id="1070475926800" name="jetbrains.mps.baseLanguage.structure.StringLiteral" flags="nn" index="Xl_RD">
        <property id="1070475926801" name="value" index="Xl_RC" />
      </concept>
      <concept id="1068498886296" name="jetbrains.mps.baseLanguage.structure.VariableReference" flags="nn" index="37vLTw">
        <reference id="1068581517664" name="variableDeclaration" index="3cqZAo" />
      </concept>
      <concept id="1225271283259" name="jetbrains.mps.baseLanguage.structure.NPEEqualsExpression" flags="nn" index="17R0WA" />
      <concept id="4972933694980447171" name="jetbrains.mps.baseLanguage.structure.BaseVariableDeclaration" flags="ng" index="19Szcq">
        <child id="5680397130376446158" name="type" index="1tU5fm" />
      </concept>
      <concept id="1068580123155" name="jetbrains.mps.baseLanguage.structure.ExpressionStatement" flags="nn" index="3clFbF">
        <child id="1068580123156" name="expression" index="3clFbG" />
      </concept>
      <concept id="1068580123159" name="jetbrains.mps.baseLanguage.structure.IfStatement" flags="nn" index="3clFbJ">
        <child id="1068580123160" name="condition" index="3clFbw" />
        <child id="1068580123161" name="ifTrue" index="3clFbx" />
      </concept>
      <concept id="1068580123136" name="jetbrains.mps.baseLanguage.structure.StatementList" flags="sn" stub="5293379017992965193" index="3clFbS">
        <child id="1068581517665" name="statement" index="3cqZAp" />
      </concept>
      <concept id="1068580123137" name="jetbrains.mps.baseLanguage.structure.BooleanConstant" flags="nn" index="3clFbT">
        <property id="1068580123138" name="value" index="3clFbU" />
      </concept>
      <concept id="1068580320020" name="jetbrains.mps.baseLanguage.structure.IntegerConstant" flags="nn" index="3cmrfG">
        <property id="1068580320021" name="value" index="3cmrfH" />
      </concept>
      <concept id="1068581242875" name="jetbrains.mps.baseLanguage.structure.PlusExpression" flags="nn" index="3cpWs3" />
      <concept id="1081506762703" name="jetbrains.mps.baseLanguage.structure.GreaterThanExpression" flags="nn" index="3eOSWO" />
      <concept id="1081773326031" name="jetbrains.mps.baseLanguage.structure.BinaryOperation" flags="nn" index="3uHJSO">
        <child id="1081773367579" name="rightExpression" index="3uHU7w" />
        <child id="1081773367580" name="leftExpression" index="3uHU7B" />
      </concept>
    </language>
    <language id="fd392034-7849-419d-9071-12563d152375" name="jetbrains.mps.baseLanguage.closures">
      <concept id="1199569711397" name="jetbrains.mps.baseLanguage.closures.structure.ClosureLiteral" flags="nn" index="1bVj0M">
        <child id="1199569906740" name="parameter" index="1bW2Oz" />
        <child id="1199569916463" name="body" index="1bW5cS" />
      </concept>
    </language>
    <language id="7a5dda62-9140-4668-ab76-d5ed1746f2b2" name="jetbrains.mps.lang.typesystem">
      <concept id="1175517767210" name="jetbrains.mps.lang.typesystem.structure.ReportErrorStatement" flags="nn" index="2MkqsV">
        <child id="1175517851849" name="errorString" index="2MkJ7o" />
      </concept>
      <concept id="1227096774658" name="jetbrains.mps.lang.typesystem.structure.MessageStatement" flags="ng" index="2OEH$v">
        <child id="1227096802790" name="nodeToReport" index="2OEOjV" />
      </concept>
      <concept id="1195213580585" name="jetbrains.mps.lang.typesystem.structure.AbstractCheckingRule" flags="ig" index="18hYwZ">
        <child id="1195213635060" name="body" index="18ibNy" />
      </concept>
      <concept id="1195214364922" name="jetbrains.mps.lang.typesystem.structure.NonTypesystemRule" flags="ig" index="18kY7G" />
      <concept id="1174642788531" name="jetbrains.mps.lang.typesystem.structure.ConceptReference" flags="ig" index="1YaCAy">
        <reference id="1174642800329" name="concept" index="1YaFvo" />
      </concept>
      <concept id="1174648085619" name="jetbrains.mps.lang.typesystem.structure.AbstractRule" flags="ng" index="1YuPPy">
        <child id="1174648101952" name="applicableNode" index="1YuTPh" />
      </concept>
      <concept id="1174650418652" name="jetbrains.mps.lang.typesystem.structure.ApplicableNodeReference" flags="nn" index="1YBJjd">
        <reference id="1174650432090" name="applicableNode" index="1YBMHb" />
      </concept>
    </language>
    <language id="7866978e-a0f0-4cc7-81bc-4d213d9375e1" name="jetbrains.mps.lang.smodel">
      <concept id="1138056022639" name="jetbrains.mps.lang.smodel.structure.SPropertyAccess" flags="nn" index="3TrcHB">
        <reference id="1138056395725" name="property" index="3TsBF5" />
      </concept>
      <concept id="1138056282393" name="jetbrains.mps.lang.smodel.structure.SLinkListAccess" flags="nn" index="3Tsc0h">
        <reference id="1138056546658" name="link" index="3TtcxE" />
      </concept>
    </language>
    <language id="ceab5195-25ea-4f22-9b92-103b95ca8c0c" name="jetbrains.mps.lang.core">
      <concept id="1169194658468" name="jetbrains.mps.lang.core.structure.INamedConcept" flags="ng" index="TrEIO">
        <property id="1169194664001" name="name" index="TrG5h" />
      </concept>
    </language>
    <language id="83888646-71ce-4f1c-9c53-c54016f6ad4f" name="jetbrains.mps.baseLanguage.collections">
      <concept id="1204796164442" name="jetbrains.mps.baseLanguage.collections.structure.InternalSequenceOperation" flags="nn" index="23sCx2">
        <child id="1204796294226" name="closure" index="23t8la" />
      </concept>
      <concept id="1203518072036" name="jetbrains.mps.baseLanguage.collections.structure.SmartClosureParameterDeclaration" flags="ig" index="Rh6nW" />
      <concept id="1162935959151" name="jetbrains.mps.baseLanguage.collections.structure.GetSizeOperation" flags="nn" index="34oBXx" />
      <concept id="1202120902084" name="jetbrains.mps.baseLanguage.collections.structure.WhereOperation" flags="nn" index="3zZkjj" />
    </language>
  </registry>
  <node concept="18kY7G" id="1VAgMjDsUii">
    <property role="TrG5h" value="unique_initial_state" />
    <node concept="3clFbS" id="1VAgMjDsUij" role="18ibNy">
      <node concept="3clFbJ" id="1VAgMjDsUi$" role="3cqZAp">
        <node concept="3eOSWO" id="1VAgMjDt6ZB" role="3clFbw">
          <node concept="3cmrfG" id="1VAgMjDt77L" role="3uHU7w">
            <property role="3cmrfH" value="1" />
          </node>
          <node concept="2OqwBi" id="1VAgMjDt7_Y" role="3uHU7B">
            <node concept="2OqwBi" id="1VAgMjDsXuM" role="2Oq$k0">
              <node concept="2OqwBi" id="1VAgMjDsVgw" role="2Oq$k0">
                <node concept="1YBJjd" id="1VAgMjDti_i" role="2Oq$k0">
                  <ref role="1YBMHb" node="1VAgMjDsUin" resolve="app" />
                </node>
                <node concept="3Tsc0h" id="1VAgMjDsVxv" role="2OqNvi">
                  <ref role="3TtcxE" to="bt66:1VAgMjDrKZi" resolve="states" />
                </node>
              </node>
              <node concept="3zZkjj" id="1VAgMjDt39b" role="2OqNvi">
                <node concept="1bVj0M" id="1VAgMjDt39d" role="23t8la">
                  <node concept="3clFbS" id="1VAgMjDt39e" role="1bW5cS">
                    <node concept="3clFbF" id="1VAgMjDt39f" role="3cqZAp">
                      <node concept="17R0WA" id="1VAgMjDt4Zw" role="3clFbG">
                        <node concept="3clFbT" id="1VAgMjDt5bK" role="3uHU7w">
                          <property role="3clFbU" value="true" />
                        </node>
                        <node concept="2OqwBi" id="1VAgMjDt39g" role="3uHU7B">
                          <node concept="37vLTw" id="1VAgMjDt39h" role="2Oq$k0">
                            <ref role="3cqZAo" node="1VAgMjDt39j" resolve="s" />
                          </node>
                          <node concept="3TrcHB" id="1VAgMjDt3uR" role="2OqNvi">
                            <ref role="3TsBF5" to="bt66:1VAgMjDs1lE" resolve="isInitial" />
                          </node>
                        </node>
                      </node>
                    </node>
                  </node>
                  <node concept="Rh6nW" id="1VAgMjDt39j" role="1bW2Oz">
                    <property role="TrG5h" value="s" />
                    <node concept="2jxLKc" id="1VAgMjDt39k" role="1tU5fm" />
                  </node>
                </node>
              </node>
            </node>
            <node concept="34oBXx" id="1VAgMjDt7Yg" role="2OqNvi" />
          </node>
        </node>
        <node concept="3clFbS" id="1VAgMjDsUiA" role="3clFbx">
          <node concept="2MkqsV" id="1VAgMjDt8a2" role="3cqZAp">
            <node concept="3cpWs3" id="1VAgMjDtpQX" role="2MkJ7o">
              <node concept="Xl_RD" id="1VAgMjDtq7R" role="3uHU7w">
                <property role="Xl_RC" value="!" />
              </node>
              <node concept="3cpWs3" id="1VAgMjDtodp" role="3uHU7B">
                <node concept="Xl_RD" id="1VAgMjDt8ah" role="3uHU7B">
                  <property role="Xl_RC" value="Duplicated initial state detected in" />
                </node>
                <node concept="2OqwBi" id="1VAgMjDtoA3" role="3uHU7w">
                  <node concept="1YBJjd" id="1VAgMjDtopS" role="2Oq$k0">
                    <ref role="1YBMHb" node="1VAgMjDsUin" resolve="app" />
                  </node>
                  <node concept="3TrcHB" id="1VAgMjDtp17" role="2OqNvi">
                    <ref role="3TsBF5" to="tpck:h0TrG11" resolve="name" />
                  </node>
                </node>
              </node>
            </node>
            <node concept="1YBJjd" id="1VAgMjDt8bk" role="2OEOjV">
              <ref role="1YBMHb" node="1VAgMjDsUin" resolve="app" />
            </node>
          </node>
        </node>
      </node>
    </node>
    <node concept="1YaCAy" id="1VAgMjDsUin" role="1YuTPh">
      <property role="TrG5h" value="app" />
      <ref role="1YaFvo" to="bt66:1VAgMjDrKZ1" resolve="App" />
    </node>
  </node>
</model>

