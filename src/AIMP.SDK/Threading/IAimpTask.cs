namespace AIMP.SDK.Threading
{
    /// <summary>
    /// Interface implementation must support asynchronous access.
    /// </summary>
    public interface IAimpTask
    {
        /// <summary>
        /// Executes the task.
        /// </summary>
        /// <param name="owner">Owner provides an ability to know if user cancel the task.
        /// You must abort current operation as soon as possible.</param>
        /// <returns>The <see cref="AimpActionResult"/> result.</returns>
        AimpActionResult Execute(IAimpTaskOwner owner);
    }
}