////
////  trait_pred.h
////  aura
////
////  Created by Camilo Sasuke Tsumanuma on 02/06/19.
////
//
//
//template <  typename PRED >
//class trait_pred :
//virtual public ::object
//{
//public:
//   
//   
//   PRED                 m_pred;
//   
//   
//   trait_pred(PRED pred) :
//   m_pred(pred)
//   {
//      
//   }
//   
//   
//   virtual ::estatus     run(::trait & trait) override
//   {
//      
//      return m_pred(trait);
//      
//   }
//   
//   
//};
//
//
//template < typename PRED >
//auto __trait_pred(PRED pred)
//{
//   
//   return __new(trait_pred < PRED >(pred));
//   
//}
//
//
//
