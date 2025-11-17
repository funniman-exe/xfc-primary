#pragma once

class fc_safe_thread
{
    private:
    bool isValid = false;
    thread *internalThread = nullptr;

    bool initCommon();

    bool closeThreadCommon( const char* loc );

    public:
    /// @brief Unique per-thread identifier (if -1, something went horribly wrong)
    int32_t m_ident = -1;

    // Creates a null thread
    fc_safe_thread();

    // Opens a new thread via vex::thread
    fc_safe_thread( int ( *callback )() );

    // Opens a new thread via vex::thread
    fc_safe_thread( void ( *callback )() );

    // Opens a new thread via vex::thread
    //fc_safe_thread( const thread inputThread );

    // Opens a new thread with the specified arguments via vex::thread
    fc_safe_thread( int ( *callback )( void* ), void *arg );

    // Opens a new thread with the specified arguments via vex::thread
    fc_safe_thread( void ( *callback )( void* ), void *arg );

    // Deconstructs the thread.
    ~fc_safe_thread();

    // Deletes the thread.
    void freeThread();

    bool isValidThread();
    static int32_t totalActiveThreads();
    static int32_t totalThreads();

    // Returns a pointer to the internal thread.
    thread *getThread();

    // Permits the thread to execute from the thread handle.
    inline void detach();

    // Gets the ID of the thread.
    int32_t get_id();

    // Stops the thread.
    void interrupt();

    // Waits until the thread has finished execution.
    void join();

    // Checks whether the thread is joinable.
    bool joinable();

    // Gets a pointer to the native handle of the thread.
    void* native_handle();

    // Gets the priority of the thread.
    int32_t priority();

    // Sets the priority of the thread.
    void setPriority( int32_t priority );

    // Swaps the thread IDs with the specified thread.
    void swap( fc_safe_thread __t );
};