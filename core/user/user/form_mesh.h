#pragma once


namespace user
{


   class CLASS_DECL_CORE form_mesh:
      virtual public ::user::form_window,
      virtual public ::user::mesh
   {
   public:


      class CLASS_DECL_CORE control_keep
      {
      public:
         inline control_keep(form_mesh * pformmesh, const ::user::item & item)
         {
            m_pformmesh                      = pformmesh;
            m_item                           = pformmesh->m_itemControl;
            pformmesh->m_itemControl         = item;
         }
         inline control_keep(form_mesh * pformmesh,const ::point & point)
         {
            m_pformmesh                      = pformmesh;
            m_item                           = pformmesh->m_itemControl;
            pformmesh->control_001DisplayHitTest(point);
         }
         inline ~control_keep()
         {
            m_pformmesh->m_itemControl      = m_item;
         }
         form_mesh *             m_pformmesh;
         item                    m_item;
      };


      __pointer(::user::interaction)     m_pcontrolEdit;

      ::count           m_iClickCount;
      item              m_itemClick;

      item              m_itemControl;


      form_mesh();
      virtual ~form_mesh();


      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001DrawSubItem(draw_mesh_item * pdrawitem) override;

      void _000OnMouse(::message::mouse * pmouse) override;


      virtual bool _001HitTest_(const ::point & point, index&iItem, index&iSubItem) override;

      void control_get_client_rect(::user::interaction * pinteraction,RECT32 * prect) override;

      void control_get_window_rect(::user::interaction * pinteraction,RECT32 * prect) override;

      bool control_001DisplayHitTest(const ::point & point);

      bool _001IsEditing() override;

      virtual bool _001IsPointInside(::user::interaction * pinteraction,point64 ptt) override;

      void _001HideEditingControls();
      void _001HideControl(::user::interaction * pinteraction);
      //virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);
      //virtual LRESULT _001BaseWndGetProperty(EProperty eprop,LPARAM lparam) override;

      ;; void _001UpdateColumns();
      ::user::interaction * _001GetEditControl();
      void _001SetEditControl(::user::interaction * pinteraction);
      virtual void _001PlaceControl(::user::interaction * pinteraction, index iEditItem, bool bClick = false, bool bOnlySizeAndPosition = false);
      virtual ::user::interaction * _001GetControl(index iItem, index iSubItem);
      virtual bool on_click(const ::user::item & item) override;
      void _001OnTimer(::timer * ptimer) override;

      virtual void _001GetSelection(::database::key & key,::database::selection & selection) override;

      DECL_GEN_SIGNAL(_001OnNotify);
      DECL_GEN_SIGNAL(_001OnMessageNotify);

      DECL_GEN_SIGNAL(_001OnVScroll);
      DECL_GEN_SIGNAL(_001OnHScroll);
      DECL_GEN_SIGNAL(_001OnKeyDown);

      virtual bool _001OnMouseActivate(::user::interaction_impl * pDesktopWnd,::u32 nHitTest,const ::id & id,LRESULT & iResult);


      virtual void install_message_routing(::channel * pchannel) override;

      virtual void on_control_event(::user::control_event * pevent) override;

      virtual bool _001OnControlSetFocus(::user::interaction * pinteraction) override;

      virtual bool _001OnControlKillFocus(::user::interaction * pinteraction) override;

      virtual bool _001OnSetItemText(::user::interaction * pinteraction,index iItem,index iSubItem);


   };


} // namespace user








