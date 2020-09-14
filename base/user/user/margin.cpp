#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif


namespace user
{


   margin_base::margin_base()
   {

      m_rectMargin.left    = 0;
      m_rectMargin.top     = 0;
      m_rectMargin.right   = 0;
      m_rectMargin.bottom  = 0;

   }


   margin_base::~margin_base()
   {

   }


   void margin_base::get_margin_rect(RECT * prectMargin)

   {

      *prectMargin = m_rectMargin;


   }


} // namespace user


