#pragma once


namespace user
{


   class place_holder;


   class CLASS_DECL_AURA impact_data :
      virtual public ::generic_object
   {
   public:


      ::i64                            m_iId;
      id                               m_id;
      __pointer(interaction)           m_puserinteraction;
      __pointer(place_holder)          m_pplaceholder;
      __pointer(document)              m_pdocument;
      id                               m_idSplit;
      bool                             m_bTabSplitSwap;
      i32                              m_iExtendOnParent;
      eflag                            m_eflag;
      ::id                             m_idTitle;
      void *                           m_pimpactdata;
      bool                             m_bOk;

      
      impact_data();
      impact_data(const ::id & id, const ::id & idTitle);
      virtual ~impact_data();

      void impact_data_common_construct();


   };



   class CLASS_DECL_AURA impact_data_map :
      public id_map < __pointer(impact_data) >
   {
   public:


   };

} // namespace user



