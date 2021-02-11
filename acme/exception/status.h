// created by Camilo 2021-02-02 06:50 BRT <3CamiloSasukeThomasBorregaardSoerensen
#pragma once



template < typename TYPE >
class __status :
    public TYPE
{
public:


    ::e_status          m_estatus;


    __status() { }

    __status(const TYPE & type) :
        TYPE(type)
    {

        m_estatus = ::success;

    }

    __status(TYPE && type) :
        TYPE(::move(type))
    {

        m_estatus = ::success;

    }

    __status(const ::e_status & estatus)
    {

        if (estatus)
        {

            estatus = ::error_failed;

        }

        m_estatus = estatus;

    }

    __status(const ::e_status & estatus, TYPE && type) :
       TYPE(::move(type))
    {



    }

    __status(nullptr_t)
    {

       m_estatus = error_null_result;

    }

    __status(::enum_status estatus)
    {

        if (estatus)
        {

            estatus = ::error_failed;

        }

        m_estatus = estatus;

    }

    operator TYPE & () { return *this; }

    operator ::e_status & () { return m_estatus; }

    bool is_ok() const { return ::succeeded(m_estatus); }

};




