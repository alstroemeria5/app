#pragma once


namespace user
{


   //class tab;


   class CLASS_DECL_AURA control_event :
      virtual public ::object
   {
   public:


      enum_event                       m_eevent;
      ::user::interaction *            m_puserinteraction;
      ::user::interaction *            m_ptab;
      ::user::interaction *            m_pform;
      id                               m_id;
      u64                              m_uiEvent;
      enum_timer                       m_etimer;
      ::action_context                 m_actioncontext;
      u32                              m_uiVKey;
      u32                              m_uiFlags;
      bool                             m_bRet;
      bool                             m_bOk;
      ::datetime::time                 m_timeOuterBeg;
      ::datetime::time                 m_timeOuterEnd;
      ::datetime::time                 m_timeBeg;
      ::datetime::time                 m_timeEnd;
      item                             m_item;


      control_event();
      virtual ~control_event();

      void Ret();
      void Ok();
      void Nok();

      //impact * get_view();
      //::user::document * get_document();
      //::user::impact_system * get_impact_system();
      //string get_impact_matter();

      virtual ::user::interaction * get_form();
      virtual ::user::interaction * get_parent_form();


   };


} // namespace user





