using System;
using System.Diagnostics.CodeAnalysis;
using System.Net;
using System.Net.Http;
using JetBrains.Annotations;
using Newtonsoft.Json;
using Nuke.Core.Tooling;

namespace Nuke.Common.Tools.SonarQube
{
    public static partial class SonarQubeTasks
    {
        public static StatusResponse SonarQubeHelthCheck(SonarQubeApiSettings configurator)
        {
            var client = new HttpClient
            {
                BaseAddress = new Uri(configurator.HostUrl)
            };

            var response = client.GetAsync("api/system/status").Result;
            if (response.StatusCode == HttpStatusCode.OK)
            {
                var stringData = response.Content.ReadAsStringAsync().Result;
                return (StatusResponse) JsonConvert.DeserializeObject(stringData, typeof(StatusResponse));
            }

            return null;
        }
    }

    public class SonarQubeApiSettings : ToolSettings
    {
        public virtual string HostUrl { get; internal set; }

    }

    [PublicAPI]
    [ExcludeFromCodeCoverage]
    public static partial class SonarQubeApiSettingsExtensions
    {
        #region HostUrl
        /// <summary><p><em>Sets <see cref="SonarQubeApiSettings.HostUrl"/>.</em></p><p></p></summary>
        [Pure]
        public static SonarQubeApiSettings SetHostUrl(this SonarQubeApiSettings toolSettings, string hostUrl)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.HostUrl = hostUrl;
            return toolSettings;
        }
        /// <summary><p><em>Resets <see cref="SonarQubeApiSettings.HostUrl"/>.</em></p><p></p></summary>
        [Pure]
        public static SonarQubeApiSettings ResetHostUrl(this SonarQubeApiSettings toolSettings)
        {
            toolSettings = toolSettings.NewInstance();
            toolSettings.HostUrl = null;
            return toolSettings;
        }
        #endregion
    }
}