//
//  dir_system.h
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 28/02/20.
//
#pragma once


namespace macos
{


   class CLASS_DECL_ACME dir_system :
      virtual public ::dir_system
   {
   public:


      ::file::path            m_strTimeFolder;
      ::file::path            m_strNetSeedFolder;

      ::file::path            m_strCommonAppData;
      ::file::path            m_strAppData;
      ::file::path            m_strPrograms;
      ::file::path            m_strCommonPrograms;

      
      dir_system();


      virtual ::estatus initialize(::generic * pobjectContext) override;

      virtual ::estatus init_system() override;
      

   };


} // namespace macos







