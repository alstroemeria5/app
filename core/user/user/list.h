#pragma once


namespace user
{


   class CLASS_DECL_CORE list :
      virtual public mesh
   {
   public:


      bool                                   m_bColumnsAdded;
      int                                    m_iImageSpacing;
      bool                                   m_bMorePlain;
      bool                                   m_bAutoCreateListHeader;
      bool                                   m_bHeaderCtrl;
      bool                                   m_bSingleColumnMode;

      __pointer(list_header)                 m_plistheader;

      draw_list_item *                       m_pdrawlistitem;

      ::user::list_column_array              m_columna;

      __pointer(simple_list_data)            m_psimplelistdata;


      ::draw2d::fastblur                     m_blur;
      index_map < ::image_pointer >          m_mapBlur;
      index_map < string >                   m_mapText;
      index_map < ::color::color >                 m_mapBackColor;
      ::draw2d::fastblur                     m_blurIcon;
      index_map < ::image_pointer >          m_mapIconBlur;
      double                                 m_dIconSaturation;
      double                                 m_dIconLightness;
      double                                 m_dIconOpacity;
      int                                    m_iIconBlur;
      int                                    m_iIconBlurRadius;
      int                                    m_iTextSpreadRadius;
      int                                    m_iTextBlurRadius;
      int                                    m_iTextBlur;
      ::rectangle_i32                                 m_rectSpot;
      ::image_pointer                        m_pimageSpot;
      ::image_pointer                        m_pimageTime;
      bool                                   m_bHighHighLight;


      list();
      ~list() override;


      inline ::core::application* get_application() const { return m_pcontext ? m_pcontext->m_pcoreapplication : nullptr; }
      inline ::core::session* get_session() const { return m_pcontext ? m_pcontext->m_pcoresession : nullptr; }
      inline ::core::system* get_system() const { return m_psystem ? m_psystem->m_pcoresystem : nullptr; }



      i32 _001CalcItemWidth(::draw2d::graphics_pointer & pgraphics, index iItem, index iSubItem) override;
      virtual i32 _001CalcItemWidth(::draw2d::graphics_pointer & pgraphics, ::write_text::font * pfont, index iItem, index iSubItem);
      virtual i32 _001CalcItemHeight(::user::style * pstyle, int iBaseHeight);
      virtual ::e_align get_draw_text_align(EView eview);
      virtual ::e_draw_text get_draw_text_flags(EView eview);


      //virtual ::index item_index(::user::interaction * pinteractionControl);
      virtual ::index subitem_index(::user::interaction * pinteractionControl);
      //virtual ::index list_item_index(::user::interaction * pinteractionControl);
      virtual ::index column_index(::user::interaction * pinteractionControl);



      __pointer(list_column) new_list_column();


      void on_hover_select_timer() override;


      void install_message_routing(::channel * pchannel) override;

      //mesh_data * GetDataInterface();
      using mesh::update_hover;
      bool update_hover(const ::point_i32& point, bool bAvoidRedraw = true) override;
      //::write_text::font * _001GetFont();
      //::write_text::font * _001GetFontHover();
      //::draw2d::pen * _001GetPenFocused();
      //::draw2d::pen * _001GetPenHighlight();
      void PreSubClassWindow() override;
      void _OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      void _001MaximizeColumnWidth(::draw2d::graphics_pointer& pgraphics, index iColumn) override;
      //virtual i32 _001CalcItemWidth(::draw2d::graphics_pointer& pgraphics, index iItem, index iSubItem) override;
      i32 _001CalcColumnWidth(::draw2d::graphics_pointer& pgraphics, index iColumn) override;
      virtual i32 _001CalcListWidth(::draw2d::graphics_pointer& pgraphics);
      void _001OnSort() override;


      inline ::user::list_column_array & column_array() { return m_columna; }

      void _001OnBeforeDeleteRange(range & range) override;
      void _001OnDeleteRange(range & range) override;
      void _001DeleteRange(range & range) override;

      // Sort
      index _001Compare(index iItem1, index iItem2) override;
      index _002Compare(index iItem1, index iItem2, index iSubItem) override;
      index _001DisplayCompare(index iDisplayItem1, index iDisplayItem2) override;


      bool is_valid_display_item(index iDisplayItem) override;
      bool is_valid_strict_item(index iStrictItem) override;


      ::size_i32 get_item_size() override;

      void _001OnSort(index iSubItem) override;
      virtual void _001OnListHeaderItemClick(index iHeaderItem);
      virtual void _001OnListHeaderItemDblClk(index iHeaderItem);
      void Filter1(const string & str) override;
      bool Filter1Step() override;


      index _001CalcDisplayTopIndex() override;
      count _001CalcDisplayItemCount() override;
      i32 _001GetGroupHeight(index iGroup) override;


      void FilterInclude(int_array & array) override;
      void FilterInclude(index iItem) override;
      void FilterExcludeAll() override;
      void FilterClose() override;
      void FilterApply() override;
      void FilterBegin() override;
      index _001StrictToDisplay(index iStrict) override;
      index _001DisplayToStrict(index iDisplay) override;
      void _001Select(index iItem, index iSubItem) override;
      void _001Highlight(index iItem, bool bRedraw) override;
      void _001RemoveSelection() override;
      bool _001OnRemoveItem(index iItem) override;
      bool _001RemoveItem(index iItem, bool bRedraw = true) override;
      void _001EnsureVisible(index iItem, ::e_align ealign = e_align_vertical_center, bool bRedraw = true);
      void _001EnsureVisible(index iItem, range & rangeRedraw) override;
      void _001ItemScroll(index iItem, bool bRedraw = true) override;
      virtual index config_id_index(const ::database::key & key);
      index _001ConfigIdToSubItem(const ::database::key & key) override;
      bool _001HasConfigId(const ::database::key & key) override;
      void _001GetSelection(::database::key & key, ::database::selection & selection) override;

      virtual void _001SetSingleColumnMode(bool bHeaderCtrl);
      //virtual bool _001InsertColumn(::user::list_column * pcolumn);
      //virtual void _001OnAfterNewColumns();
      void set_data_interface(mesh_data * pinterface) override;
      void cache_hint() override;
      //void SetCacheInterface(mesh_cache_interface * pinterface);
      //void AddMessageHandling(::channel * pchannel);
      void _001ShowTopText(bool bShow = true) override;
      void _001LayoutTopText(::draw2d::graphics_pointer& pgraphics) override;
      void _001SetTopText(const widechar * pcwsz) override;

      bool DIDDXHeaderLayout(bool bSave) override;


      void data_get_DisplayToStrict() override;
      void data_set_DisplayToStrict() override;
      id data_get_current_sort_id() override;
      id data_get_sort_id(EView eview) override;
      virtual id data_get_current_list_layout_id();

      bool query_drop(index iDisplayDrop, index iDisplayDrag) override;
      bool do_drop(index iDisplayDrop, index iDisplayDrag) override;
      bool defer_drop(index iDisplayDrop, index iDisplayDrag) override;



      virtual bool CreateHeaderCtrl();

      void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001DrawGroups(draw_list_item * pdrawitem, index iGroupFirst, index iGroupLast, index iItemFirst, index iItemLast);

      virtual void _001DrawGroup(draw_list_item * pdrawitem);

      virtual void _001DrawItems(draw_list_item * pdrawitem, index iItemFirst, index iItemLast);

      virtual void _001DrawItem(draw_list_item * pdrawitem);

      virtual void _001DrawSubItem(draw_list_item * pdrawitem);

      //virtual void _001GetItemImage(list_item * pitem);

      //virtual void _001GetItemText(list_item * pitem);

      //virtual void _001GetItemColor(list_item * pitem);

      //virtual void _001SearchGetItemText(list_item * pitem);

      ::count _001GetGroupItemCount(index iGroup) override;

      ::count _001GetGroupMetaItemCount(index iGroup) override;

      //virtual void _001GetGroupText(list_item * pitem);

      //virtual void _001GetGroupImage(list_item * pitem);

      virtual void _001InsertColumns();

      ::count _001GetColumnCount() override;


      virtual __pointer(::user::list_header) create_list_header();
      __pointer(::user::mesh_data) create_mesh_data() override;

      void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      bool _001OnUpdateItemCount(u32 dwFlags = 0) override;

      void on_change_view_size(::draw2d::graphics_pointer & pgraphics) override;


      void _001OnInitialize() override;


      //virtual __pointer(list_column) new_column();
      virtual void _001OnAddColumn(list_column * pcolumn);

      virtual void _001GetGroupRect(draw_list_item * pitem);
      virtual void _001GetItemRect(draw_list_item * pitem);
      virtual void _001GetSubItemRect(draw_list_item * pitem);
      virtual void _001GetElementRect(draw_list_item * pitem, ::user::mesh::enum_element eelement);

      virtual ::user::interaction * get_subitem_control(::index iSubItem);

      virtual void _001OnColumnChange();

      bool _001SetColumnWidth(index iColumn, i32 iWidth) override;

      virtual void _001GetColumnWidth(draw_list_item * pdrawitem);

      index _001MapSubItemToOrder(index iSubItem) override;

      index _001MapOrderToSubItem(index iOrder) override;

      index _001MapOrderToColumn(index iOrder) override;

      index _001MapColumnToOrder(index iColumn) override;

      index _001MapSubItemToColumn(index iSubItem) override;

      index _001MapColumnToSubItem(index iColumn) override;

      void _001DeleteColumn(index iColumn);


      ::count _001GetItemCount() override;
      ::count _001GetGroupCount() override;


      bool _001HitTest_(const ::point_i32 & point, index & iItem, index & iSubItem, index & iListItem, ::user::mesh::enum_element & eelement) override;
      bool _001HitTest_(const ::point_i32 & point, index & iItem, index & iSubItem) override;
      bool _001HitTest_(const ::point_i32 & point, index & iItemParam) override;


      bool _001DisplayHitTest(const ::point_i32 & point, index & iItem, index & iSubItem, index & iListItem, ::user::mesh::enum_element & eelement) override;
      bool _001DisplayHitTest(const ::point_i32 & point, index & iItem, index & iSubItem) override;
      bool _001DisplayHitTest(const ::point_i32 & point, index & iItemParam) override;


      void _001OnAfterSort() override;


      virtual void LayoutHeaderCtrl();

      void auto_arrange(bool bAutoArrange = true) override;

      bool get_auto_arrange() override;

      void on_create_draw_item() override;

      DECLARE_MESSAGE_HANDLER(on_message_size);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);
      DECLARE_MESSAGE_HANDLER(on_message_right_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      void _001OnTimer(::timer * ptimer) override;

      DECLARE_MESSAGE_HANDLER(_001OnUpdateListViewAutoArrange);

      DECLARE_MESSAGE_HANDLER(_001OnListViewAutoArrange);


      bool on_click(const ::user::item & item) override;
      bool on_right_click(const ::user::item & item) override;

      void _001GetSelection(range & selection) override;
      virtual index _001GetCurItem();

      virtual void _001SelectItem(index iItem);

      bool _001IsEditing() override;


      ::count _001GetSelectedItemCount() override;
      virtual ::count _001GetSelectedItems(index_array & ia);


      string _001GetColumnText(index iColumn) override;

      virtual void HeaderCtrlLayout();

      virtual index HeaderCtrlMapColumnToOrder(index iColumn);

      virtual bool _001OnHeaderCtrlEndDrag(wparam wparam, lparam lparam);



      bool _001OnHeaderCtrlEndTrack(wparam wparam, lparam lparam) override;


      bool _001OnHeaderCtrlTrack(wparam wparam, lparam lparam) override;


      void _001ShowSubItem(index iSubItem, bool bShow = true) override;
      void DISaveOrder() override;

      void DILoadOrder() override;


      void _001OnSelectionChange() override;

      virtual void _001UpdateColumns();


      virtual void _001RemoveAllColumns();


      virtual void _001CreateImageList(list_column * pcolumn);

      bool _001IsItemVisible(index iItem) override;

      virtual void _001ClearSelection();

      void _001SetSelection(const range & range) override;

      void _001AddSelection(const item_range & itemrange) override;

      ::e_status set_current_item(const ::user::item & item, const ::action_context & action_context) override;
      ::user::item current_item() override;

      void set_current_item(const index_array & iaSel, const ::action_context & action_context) override;
      void get_cur_sel(index_array & iaSel) override;

      void _001SetHighlightRange(range & range) override;

      //void _001SetView(EView eview, bool bLayout = true);

      EView _001GetView() override;


      virtual i32 get_wheel_scroll_delta() override;

      virtual void on_change_viewport_offset(::draw2d::graphics_pointer & pgraphics) override;

      virtual bool keyboard_focus_is_focusable() const override;

      DECLARE_MESSAGE_HANDLER(_001OnVScroll);
      DECLARE_MESSAGE_HANDLER(_001OnHScroll);

      virtual void _thread_data_update_visible_subitem() override;

      virtual void defer_create_mesh_data() override;

      virtual void on_viewport_offset(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;

      //virtual bool get_client_rect(RECTANGLE_I32 * prectangle) override;


      virtual void update_icon_list_view_sort();

   };


} // namespace user




