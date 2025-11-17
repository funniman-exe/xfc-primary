#include "vex.h"

using namespace vex;

#include "fc_safe_thread.h"

#include "fc_log.h"

static int32_t __totalActiveThreads = 0;
static int32_t __totalThreads = 0;


bool fc_safe_thread::initCommon()
{
    if ( m_ident == -1 )
        m_ident = ++__totalThreads;

    if ( __totalActiveThreads + 1 > thread::hardware_concurrency() )
    {
        fc_log( logTypes::ERROR, false, true, __func__, "Attempted to open TOO MANY THREADS (Max is %d)!\n", thread::hardware_concurrency() );
        return false;
    }

    ++__totalActiveThreads;
    fc_log( logTypes::Debug, false, true, __func__, "Opening new thread (%d).\n", m_ident );
    return true;
}

fc_safe_thread::fc_safe_thread()
{
    if ( m_ident == -1 )
        m_ident = ++__totalThreads;

    internalThread = nullptr;
    isValid = false;
}

fc_safe_thread::fc_safe_thread( int ( *callback )() )
{
    if ( !initCommon() )
        return;

    internalThread = new thread( callback );
    isValid = true;
}

fc_safe_thread::fc_safe_thread( void ( *callback )() )
{
    if ( !initCommon() )
        return;

    internalThread = new thread( callback );
    isValid = true;
}

/*fc_safe_thread::fc_safe_thread( const thread inputThread )
{
    if ( !initCommon() )
        return;

    internalThread = new thread( inputThread );
    isValid = true;
}*/

fc_safe_thread::fc_safe_thread( int ( *callback )( void* ), void *arg )
{
    if ( !initCommon() )
        return;

    internalThread = new thread( callback, arg );
    isValid = true;
}

fc_safe_thread::fc_safe_thread( void ( *callback )( void* ), void *arg )
{
    if ( !initCommon() )
        return;

    internalThread = new thread( callback, arg );
    isValid = true;
}

bool fc_safe_thread::closeThreadCommon( const char* loc )
{
    if ( isValid )
    {
        fc_log( logTypes::Debug, false, true, loc, "Closing thread (%d).\n", m_ident );
        isValid = false;
        internalThread->interrupt();
        delete internalThread;
        internalThread = nullptr;
        return true;
    }
    else
    {
        fc_log( logTypes::Debug, false, true, loc, "Attempted to close thread (%d), but it was already closed?\n", m_ident );
        return false;
    }
}

fc_safe_thread::~fc_safe_thread()
{
    closeThreadCommon( __func__ );
    --__totalThreads;
    fc_log( logTypes::Debug, false, true, __func__, "Thread has been deleted (%d).\n", m_ident );
}

void fc_safe_thread::freeThread()
{
    closeThreadCommon( __func__ );
}

bool fc_safe_thread::isValidThread()
{
    return isValid;
}

int32_t fc_safe_thread::totalActiveThreads()
{
    return __totalActiveThreads;
}

int32_t fc_safe_thread::totalThreads()
{
    return __totalThreads;
}

thread *fc_safe_thread::getThread()
{
    if ( !isValid )
    {
        fc_log( logTypes::ERROR, false, true, __func__, "Accessing NULL thread! This may cause unexpected behaviour (%d).\n", m_ident );
        return NULL;
    }

    return internalThread;
}

void fc_safe_thread::detach()
{
    if ( !isValid )
    {
        fc_log( logTypes::ERROR, false, true, __func__, "Tried to detach NULL thread (%d)!\n", m_ident );
        return;
    }

    internalThread->detach();
}

int32_t fc_safe_thread::get_id()
{
    if ( !isValid )
    {
        fc_log( logTypes::ERROR, false, true, __func__, "Accessing NULL thread! This may cause unexpected behaviour (%d).\n", m_ident );
        return -1;
    }

    return internalThread->get_id();
}

void fc_safe_thread::interrupt()
{
    if ( !isValid )
    {
        fc_log( logTypes::ERROR, false, true, __func__, "Tried to interrupt NULL thread (%d)!\n", m_ident );
        return;
    }

    internalThread->interrupt();
}

void fc_safe_thread::join()
{
    if ( !isValid )
    {
        fc_log( logTypes::ERROR, false, true, __func__, "Tried to join NULL thread (%d)!\n", m_ident );
        return;
    }

    internalThread->join();
}

bool fc_safe_thread::joinable()
{
    if ( !isValid )
    {
        fc_log( logTypes::ERROR, false, true, __func__, "Accessing NULL Thread! This may cause unexpected behaviour (%d).\n", m_ident );
        return false;
    }

    return internalThread->joinable();
}

void* fc_safe_thread::native_handle()
{
    if ( !isValid )
    {
        fc_log( logTypes::ERROR, false, true, __func__, "Accessing NULL Thread! This may cause unexpected behaviour (%d).\n", m_ident );
        return NULL;
    }

    return internalThread->native_handle();
}

int32_t fc_safe_thread::priority()
{
    if ( !isValid )
    {
        fc_log( logTypes::ERROR, false, true, __func__, "Accessing NULL Thread! This may cause unexpected behaviour (%d).\n", m_ident );
        return -1;
    }

    return internalThread->priority();
}

void fc_safe_thread::setPriority( int32_t priority )
{
    if ( !isValid )
    {
        fc_log( logTypes::ERROR, false, true, __func__, "Tried to set priority of NULL thread (%d).\n", m_ident );
        return;
    }

    internalThread->setPriority( priority );
}

void fc_safe_thread::swap( fc_safe_thread __t )
{
    if ( !isValid )
    {
        fc_log( logTypes::ERROR, false, true, __func__, "Tried to swap NULL thread (%d <--> %d).\n", m_ident, __t.m_ident );
        return;
    }
    
    if ( !__t.isValidThread() )
    {
        fc_log( logTypes::ERROR, false, true, __func__, "Tried to swap with NULL thread (%d <--> %d).\n", m_ident, __t.m_ident  );
        return;
    }

    internalThread->swap( *__t.getThread() );
}