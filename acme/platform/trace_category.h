#pragma once


class CLASS_DECL_ACME trace_category :
   virtual public matter
{
public:


   e_trace_category     m_ecategory;
   string               m_strTopicText;
   bool                 m_bEnable;


   static __pointer_array(trace_category) * s_ptracecategorya;

   

   trace_category(e_trace_category etracecategory, const char * pszTopicText) :
      m_ecategory(etracecategory),
      m_strTopicText(pszTopicText)
   {

   }


};

