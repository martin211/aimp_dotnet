namespace AIMP.SDK.Services
{
    using System;

    /// <summary>
    /// 
    /// </summary>
    public interface IAimpPropertyList
    {
        /// <summary>
        /// Begins the update.
        /// </summary>
        void BeginUpdate();

        /// <summary>
        /// Ends the update.
        /// </summary>
        void EndUpdate();

        /// <summary>
        /// Resets this instance.
        /// </summary>
        void Reset();

        /// <summary>
        /// Gets the value as float.
        /// </summary>
        /// <param name="propertyId">The property identifier.</param>
        /// <returns></returns>
        float GetValueAsFloat(int propertyId);

        /// <summary>
        /// Gets the value as int32.
        /// </summary>
        /// <param name="propertyId">The property identifier.</param>
        /// <returns></returns>
        int GetValueAsInt32(int propertyId);

        /// <summary>
        /// Gets the value as int64.
        /// </summary>
        /// <param name="propertyId">The property identifier.</param>
        /// <returns></returns>
        Int64 GetValueAsInt64(int propertyId);

        /// <summary>
        /// Gets the value as object.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="propertyId">The property identifier.</param>
        /// <param name="objectId">The object identifier.</param>
        /// <returns></returns>
        T GetValueAsObject<T>(int propertyId, int objectId);

        /// <summary>
        /// Sets the value as float.
        /// </summary>
        /// <param name="propertyId">The property identifier.</param>
        /// <param name="value">The value.</param>
        void SetValueAsFloat(int propertyId, float value);

        /// <summary>
        /// Sets the value as int32.
        /// </summary>
        /// <param name="propertyId">The property identifier.</param>
        /// <param name="value">The value.</param>
        void SetValueAsInt32(int propertyId, int value);

        /// <summary>
        /// Sets the value as int64.
        /// </summary>
        /// <param name="propertyId">The property identifier.</param>
        /// <param name="value">The value.</param>
        void SetValueAsInt64(int propertyId, Int64 value);

        /// <summary>
        /// Sets the value as object.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="propertyId">The property identifier.</param>
        /// <param name="value">The value.</param>
        void SetValueAsObject<T>(int propertyId, T value);
    }
}