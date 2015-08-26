namespace AIMP.SDK.Services
{
    public enum ActionResult
    {
        /// <summary>
        /// Operation completed.
        /// </summary>
        Ok,

        /// <summary>
        /// Cross-thread operation not valid
        /// </summary>
        AccessDenied,

        /// <summary>
        /// Object already disposed
        /// </summary>
        Handle,

        /// <summary>
        /// Invalid arguments.
        /// </summary>
        InvalidArguments,

        /// <summary>
        /// Not implemented.
        /// </summary>
        NotImplemented,

        /// <summary>
        /// Unexpe3cted error.
        /// </summary>
        Unexpected,

        /// <summary>
        /// Failed.
        /// </summary>
        Fail
    }
}