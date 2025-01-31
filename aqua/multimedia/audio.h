#pragma once


namespace aqua
{


   class CLASS_DECL_AQUA audio :
      virtual public ::acme::department
   {
   public:


      ::audio::audio *     m_paudio;
      bool                 m_bLocalFileSystemSynch;
      ::duration           m_durationPreBuffer;


      audio();
      virtual ~audio();


      virtual void play_audio(::file::file * pfile, bool bSynch = false);


      virtual __pointer(::tts::speaker) create_tts_speaker();

      virtual void speak(const ::string & strText);
      virtual void speak(const ::string & strLang, const ::string & strText, bool bSynch);
      virtual void trans_speak(const ::string & strLang, const ::string & strText, bool bSynch);
      virtual void google_speak(const ::string & strLang, const ::string & strText, bool bSynch);


      virtual ::file_pointer get_rtp_file(const ::payload & varFile);


      virtual LPFN_NEW_MULTIMEDIA_DECODER get_multimedia_decoder_factory(const ::string & pszTitle);


      virtual LPWAVEOUT waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback);


      virtual ::e_status defer_initialize_audio_playback(::wave::e_purpose epurpose = ::wave::purpose_playground);


   };


} // namespace aqua

//extern "C"
//typedef ::aqua::audio * GET_NEW_AUDIO();

//typedef GET_NEW_AUDIO * PFUNCTION_GET_NEW_AUDIO;

//CLASS_DECL_AQUA void set_get_new_audio(PFUNCTION_GET_NEW_AUDIO pfunction);

//extern "C"
//CLASS_DECL_AQUA ::aqua::audio * get_get_new_audio();


///CLASS_DECL_AQUA ::aqua::audio * get_context_audio(::object * pobject);



//namespace audio
//{
//
//
//   CLASS_DECL_AQUA string get_default_library_name();
//
//
//} // namespace audio
//


