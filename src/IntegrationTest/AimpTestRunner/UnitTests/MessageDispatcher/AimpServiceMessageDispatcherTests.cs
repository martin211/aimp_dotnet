// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;
using AIMP.SDK;
using AIMP.SDK.MessageDispatcher;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.MessageDispatcher
{
    [TestFixture]
    public class AimpServiceMessageDispatcherTests : AimpIntegrationTest
    {
        private class TestHook : IAimpMessageHook
        {
            private readonly Action<AimpCoreMessageType, int, IntPtr> _callBack;

            public TestHook()
            {
            }

            public TestHook(Action<AimpCoreMessageType, int, IntPtr> callBack)
            {
                _callBack = callBack;
            }

            public AimpActionResult CoreMessage(AimpCoreMessageType message, int param1, IntPtr param2)
            {
                _callBack?.Invoke(message, param1, param2);
                TestContext.Write($"Receive hook: {message}, p1: {param1}, p2: {param2}");
                return new AimpActionResult(ActionResultType.OK);
            }
        }

        public override void RunBeforeAnyTests()
        {
            base.RunBeforeAnyTests();
            //Player.ServicePlaylistManager.CreatePlaylistFromFile(PlaylistPath, false);
            //Player.ServicePlaylistManager.CreatePlaylistFromFile(PlaylistPath, true);
            //Player.ServicePlaylistManager.CreatePlaylistFromFile(PlaylistPath, false);
        }

        [Test]
        [Order(1)]
        public void Hook_ShouldSetHook()
        {
            ExecuteInMainThread(() =>
            {
                var hook = new TestHook();
                var result = Player.ServiceMessageDispatcher.Hook(hook);
                this.AreEqual(ActionResultType.OK, result.ResultType, "Cannot hook a new hook");
                Player.ServiceMessageDispatcher.Unhook(hook);
            });
        }

        [Test]
        [Order(2)]
        public void Unhook_ShouldUnhook()
        {
            ExecuteInMainThread(() =>
            {
                var hook = new TestHook();

                Player.ServiceMessageDispatcher.Hook(hook);

                var result = Player.ServiceMessageDispatcher.Unhook(hook);
                this.AreEqual(ActionResultType.OK, result.ResultType, "Cannot unhook a hook");
            });
        }

        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdAbout)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdAddFiles)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdAddFolders)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdAddPlaylists)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdAddUrl)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdBookmarks)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdBookmarksAdd)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdDSPManager)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdNext)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdOpenFiles)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdOpenFolders)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdOpenPlaylists)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdOptions)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdPause)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdPlay)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdPlayPause)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdPlayPrevPlaylist)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdPlaylistDeleteAll)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdPlaylistDeleteDuplicates)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdPlaylistDeleteNonExists)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdPlaylistDeleteNonSelected)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdPlaylistDeletePlayingFromHDD)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdPlaylistDeleteSwitchedOff)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdPlaylistDeleteSwitchedOffFromHDD)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdPlaylistFocusPlaying)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdPlaylistReloadFromPreimage)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdPlaylistRescan)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdPlaylistRescanSelected)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdPlaylistSortByArtist)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdPlaylistSortByDuration)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdPlaylistSortByPath)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdPlaylistSortByTitle)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdPlaylistSortInvert)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdPlaylistSortRandomize)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdPlaylistSwitchOn)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdPlaylistSwitchOff)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdPlugins)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdPrev)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdQFIPlaybackTrack)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdQTEPlayingTrack)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdQuit)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdShowNotification)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdSavePlaylists)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdScheduler)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdSearch)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdStop)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdTogglePartRepeat)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdVisualNext)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdVisualPrev)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdVisualStart)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdVisualStop)]
        [TestCase(AimpCoreMessageType.CmdStateGet, AimpCoreMessageType.CmdQFI)]
        public void Send_CheckIsCommandAllowed_ShouldBeOK(AimpCoreMessageType messageType, AimpCoreMessageType param1)
        {
            ExecuteInMainThread(() =>
            {
                var result = Player.ServiceMessageDispatcher.Send(messageType, (int)param1, IntPtr.Zero);
                this.IsTrue(result.ResultType == ActionResultType.OK || result.ResultType == ActionResultType.Fail || result.ResultType == ActionResultType.NotImplemented, $"Current value {result.ResultType}");
            });
        }

        [TestCase(AimpCoreMessageType.PropertyEcho, 0.5, Description = "Set echo to 0.5")]
        [TestCase(AimpCoreMessageType.PropertyBalance, 0.5, Description = "Set balance to 0.5")]
        [TestCase(AimpCoreMessageType.PropertyChorus, 0.5, Description = "Set chorus to 0.5")]
        [TestCase(AimpCoreMessageType.PropertyCrossmixing, true, Description = "Enable Crossmixing")]
        [TestCase(AimpCoreMessageType.PropertyCrossmixing, false, Description = "Disable Crossmixing")]
        [TestCase(AimpCoreMessageType.PropertyEnhancer, 1.5, Description = "Set Enhancer to 1.5")]
        [TestCase(AimpCoreMessageType.PropertyEqualizer, true, Description = "Enable Equalizer")]
        [TestCase(AimpCoreMessageType.PropertyEqualizer, false, Description = "Disable Equalizer")]
        [TestCase(AimpCoreMessageType.PropertyFlanger, 0.5, Description = "Set Flanger to 0.5")]
        [TestCase(AimpCoreMessageType.PropertyMinimizedToTray, true)]
        [TestCase(AimpCoreMessageType.PropertyMinimizedToTray, false)]
        [TestCase(AimpCoreMessageType.PropertyMute, true)]
        [TestCase(AimpCoreMessageType.PropertyMute, false)]
        [TestCase(AimpCoreMessageType.PropertyPitch, 2.1)]
        [TestCase(AimpCoreMessageType.PropertyPlayerBuffering, 50.5)]
        [TestCase(AimpCoreMessageType.PropertyPlayerPosition, 10.5)]
        [TestCase(AimpCoreMessageType.PropertyPreamp, 10.5)]
        [TestCase(AimpCoreMessageType.PropertyRadioCap, true)]
        [TestCase(AimpCoreMessageType.PropertyRadioCap, false)]
        [TestCase(AimpCoreMessageType.PropertyRadioCapSingleTrack, true)]
        [TestCase(AimpCoreMessageType.PropertyRadioCapSingleTrack, false)]
        [TestCase(AimpCoreMessageType.PropertyRepeat, true)]
        [TestCase(AimpCoreMessageType.PropertyRepeat, false)]
        [TestCase(AimpCoreMessageType.PropertyRepeatSingleFilePlaylists, true)]
        [TestCase(AimpCoreMessageType.PropertyRepeatSingleFilePlaylists, false)]
        [TestCase(AimpCoreMessageType.PropertyReverb, 0.5, Description = "Set Reverb to 0.5")]
        [TestCase(AimpCoreMessageType.PropertyReverseTime, true)]
        [TestCase(AimpCoreMessageType.PropertyReverseTime, false)]
        [TestCase(AimpCoreMessageType.PropertyShuffle, true)]
        [TestCase(AimpCoreMessageType.PropertyShuffle, false)]
        [TestCase(AimpCoreMessageType.PropertySpeed, 1.1)]
        [TestCase(AimpCoreMessageType.PropertyStayOnTop, true, Description = "Enable Stay on top")]
        [TestCase(AimpCoreMessageType.PropertyStayOnTop, false, Description = "Disable Stay on top")]
        [TestCase(AimpCoreMessageType.PropertyTempo, 1.1)]
        [TestCase(AimpCoreMessageType.PropertyTruebass, 1.1)]
#if !DEBUG
        [TestCase(AimpCoreMessageType.PropertyVisualFullscreen, true)]
        [TestCase(AimpCoreMessageType.PropertyVisualFullscreen, false)]
#endif
        [TestCase(AimpCoreMessageType.PropertyVolume, 0.5)]
        [Ignore("Should reset to default before run")]
        public void Send_PropertyValueSet_ShouldBeCorrect(AimpCoreMessageType command, object param2)
        {
            ExecuteInMainThread(() =>
            {
                bool validate = true;
                IntPtr outParam2 = IntPtr.Zero;
                AimpCoreMessageType outType = AimpCoreMessageType.CmdAbout;

                var hook = new TestHook((t, p1, p2) =>
                {
                    if (validate && p1 == (int) AimpCoreMessageType.PropertyValueSet)
                    {
                        outType = t;
                        outParam2 = p2;
                    }

                    validate = false;
                });
                var result = Player.ServiceMessageDispatcher.Hook(hook);
                this.AreEqual(ActionResultType.OK, result.ResultType, "Cannot register a new hook");

                if (!IsValid)
                {
                    return;
                }

                var cmdResult = Player.ServiceMessageDispatcher.Send(command, (int)AimpCoreMessageType.PropertyValueSet, param2.ToPointer());
                this.AreEqual(ActionResultType.OK, cmdResult.ResultType);
                this.IsTrue(outParam2 != IntPtr.Zero);
                Player.ServiceMessageDispatcher.Unhook(hook);

                if (!IsValid)
                {
                    return;
                }

                switch (outType)
                {
                    case AimpCoreMessageType.PropertyStayOnTop:
                    case AimpCoreMessageType.PropertyCrossmixing:
                    case AimpCoreMessageType.PropertyEqualizer:
                    case AimpCoreMessageType.PropertyMinimizedToTray:
                    case AimpCoreMessageType.PropertyMute:
                    case AimpCoreMessageType.PropertyRadioCap:
                    case AimpCoreMessageType.PropertyRadioCapSingleTrack:
                    case AimpCoreMessageType.PropertyRepeat:
                    case AimpCoreMessageType.PropertyRepeatSingleFilePlaylists:
                    case AimpCoreMessageType.PropertyShuffle:
                        this.AreEqual(param2, outParam2.ToBool());
                        break;
                    case AimpCoreMessageType.PropertyEcho:
                    case AimpCoreMessageType.PropertyBalance:
                    case AimpCoreMessageType.PropertyChorus:
                    case AimpCoreMessageType.PropertyEnhancer:
                    case AimpCoreMessageType.PropertyPitch:
                    case AimpCoreMessageType.PropertyPlayerBuffering:
                    case AimpCoreMessageType.PropertyPlayerPosition:
                    case AimpCoreMessageType.PropertyPreamp:
                    case AimpCoreMessageType.PropertyReverb:
                    case AimpCoreMessageType.PropertyReverseTime:
                    case AimpCoreMessageType.PropertySpeed:
                    case AimpCoreMessageType.PropertyTempo:
                    case AimpCoreMessageType.PropertyTruebass:
                    case AimpCoreMessageType.PropertyVisualFullscreen:
                    case AimpCoreMessageType.PropertyVolume:
                        this.AreEqual(param2, outParam2.ToDouble());
                        break;
                }
            });
        }

        [TestCase(AimpDescriptorType.MainForm)]
        [TestCase(AimpDescriptorType.Application)]
        [TestCase(AimpDescriptorType.TrayControl)]
        [TestCase(AimpDescriptorType.PlaylistForm)]
        [TestCase(AimpDescriptorType.EqualizerForm)]
        [Ignore("Not working?")]
        public void Send_HWND_ShouldReturnDescriptor(AimpDescriptorType windowId)
        {
            ExecuteInMainThread(() =>
            {
                bool validate = true;
                IntPtr outParam2 = IntPtr.Zero;
                AimpCoreMessageType outType = AimpCoreMessageType.CmdAbout;

                var hook = new TestHook((t, p1, p2) =>
                {
                    if (validate && p1 == (int) AimpCoreMessageType.PropertyValueSet)
                    {
                        outType = t;
                        outParam2 = p2;
                    }

                    validate = false;
                });

                var result = Player.ServiceMessageDispatcher.Hook(hook);
                this.AreEqual(ActionResultType.OK, result.ResultType, "Cannot register a new hook");

                if (!IsValid)
                {
                    return;
                }

                var cmdResult = Player.ServiceMessageDispatcher.Send(AimpCoreMessageType.PropertyHwnd, (int)windowId, IntPtr.Zero);
                this.AreEqual(ActionResultType.OK, cmdResult.ResultType);

                this.IsTrue(outParam2 != IntPtr.Zero);

                Player.ServiceMessageDispatcher.Unhook(hook);
            });
        }

        [Test]
        public void Register_EmptyMessage_ShouldThrowException()
        {
            ExecuteInMainThread(() =>
            {
                this.Throw<ArgumentNullException>(() => Player.ServiceMessageDispatcher.Register(string.Empty));
            });
        }

        [Test]
        public void Register_ShouldReturnMessageId()
        {
            ExecuteInMainThread(() =>
            {
                var result = Player.ServiceMessageDispatcher.Register("Test");
                this.IsTrue(result > 0);
            });
        }

        [Test]
        public void Hook_Null_ShouldThrowException()
        {
            ExecuteInMainThread(() =>
            {
                this.Throw<ArgumentNullException>(() => Player.ServiceMessageDispatcher.Hook(null));
            });
        }
    }
}