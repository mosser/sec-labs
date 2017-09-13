package ArduinoML.editor;

/*Generated by MPS */

import jetbrains.mps.nodeEditor.EditorAspectDescriptorBase;
import org.jetbrains.annotations.NotNull;
import java.util.Collection;
import jetbrains.mps.openapi.editor.descriptor.ConceptEditor;
import org.jetbrains.mps.openapi.language.SAbstractConcept;
import java.util.Collections;
import jetbrains.mps.openapi.editor.descriptor.SubstituteMenu;
import jetbrains.mps.lang.smodel.ConceptSwitchIndex;
import jetbrains.mps.lang.smodel.ConceptSwitchIndexBuilder;
import jetbrains.mps.smodel.adapter.ids.MetaIdFactory;

public class EditorAspectDescriptorImpl extends EditorAspectDescriptorBase {
  @NotNull
  public Collection<ConceptEditor> getDeclaredEditors(SAbstractConcept concept) {
    SAbstractConcept cncpt_a0a = ((SAbstractConcept) concept);
    switch (index_xbvbvu_a0a.index(cncpt_a0a)) {
      case 0:
        return Collections.<ConceptEditor>singletonList(new Action_Editor());
      case 1:
        return Collections.<ConceptEditor>singletonList(new Actuator_Editor());
      case 2:
        return Collections.<ConceptEditor>singletonList(new App_Editor());
      case 3:
        return Collections.<ConceptEditor>singletonList(new State_Editor());
      default:
    }
    return Collections.<ConceptEditor>emptyList();
  }


  @NotNull
  @Override
  public Collection<SubstituteMenu> getDeclaredDefaultSubstituteMenus(SAbstractConcept concept) {
    SAbstractConcept cncpt_a0d = concept;
    switch (index_xbvbvu_a0d.index(cncpt_a0d)) {
      case 0:
        return Collections.<SubstituteMenu>singletonList(new Action_SubstituteMenu());
      case 1:
        return Collections.<SubstituteMenu>singletonList(new State_SubstituteMenu());
      default:
    }
    return Collections.<SubstituteMenu>emptyList();
  }

  private static final ConceptSwitchIndex index_xbvbvu_a0a = new ConceptSwitchIndexBuilder().put(MetaIdFactory.conceptId(0x6d84bad7eb044249L, 0x8d80c9157947c3f2L, 0x1ee64324e96f0fc7L), MetaIdFactory.conceptId(0x6d84bad7eb044249L, 0x8d80c9157947c3f2L, 0x1ee64324e96f0fcdL), MetaIdFactory.conceptId(0x6d84bad7eb044249L, 0x8d80c9157947c3f2L, 0x1ee64324e96f0fc1L), MetaIdFactory.conceptId(0x6d84bad7eb044249L, 0x8d80c9157947c3f2L, 0x1ee64324e96f0fc4L)).seal();
  private static final ConceptSwitchIndex index_xbvbvu_a0d = new ConceptSwitchIndexBuilder().put(MetaIdFactory.conceptId(0x6d84bad7eb044249L, 0x8d80c9157947c3f2L, 0x1ee64324e96f0fc7L), MetaIdFactory.conceptId(0x6d84bad7eb044249L, 0x8d80c9157947c3f2L, 0x1ee64324e96f0fc4L)).seal();
}
