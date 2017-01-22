namespace AIMP.SDK
{
    public enum AimpActionResult : uint
    {
        /// <summary>
        /// Operation successful.
        /// </summary>
        Ok = 0x00000000,

        /// <summary>
        /// General access denied error.
        /// </summary>
        AccessDenied = 0x80070005,

        /// <summary>
        /// Handle that is not valid.
        /// </summary>
        Handle = 0x80070006,

        /// <summary>
        /// One or more arguments are not valid.
        /// </summary>
        InvalidArguments = 0x80070057,

        /// <summary>
        /// Not implemented.
        /// </summary>
        NotImplemented = 0x80004001,

        /// <summary>
        /// Unexpected failure.
        /// </summary>
        Unexpected = 0x8000FFFF,

        /// <summary>
        /// Unspecified failure.
        /// </summary>
        Fail = 0x80004005
    }
}