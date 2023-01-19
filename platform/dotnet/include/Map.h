#pragma once
#include "Enums.h"
#include "NativeWrapper.h"
#include "Point.h"
#include <functional>
#include <msclr/gcroot.h>

namespace mbgl
{
	class Map;
	class MapObserver;
}

namespace DOTNET_NAMESPACE
{
    ref class AnimationOptions;
    ref class BoundOptions;
	ref class CameraOptions;
	ref class ClientOptions;
    ref class EdgeInsets;
    ref class FreeCameraOptions;
    ref class LatLngBounds;
	ref class MapObserver;
	ref class MapOptions;
    ref class ProjectionMode;
	interface class IRendererFrontend;
	ref class ResourceOptions;
    ref class Size;
	ref class Style;
    ref class TransformState;

    using FreeCameraOptions_ = FreeCameraOptions;
    using MapOptions_ = MapOptions;
    using ProjectionMode_ = ProjectionMode;
	using Style_ = Style;
    using TransformState_ = TransformState;
	
	public enum class MapDebugOptions : System::UInt32
	{
		NoDebug = 0,
		TileBorders = 1 << 1,
		ParseStatus = 1 << 2,
		Timestamps = 1 << 3,
		Collision = 1 << 4,
		Overdraw = 1 << 5,
		StencilClip = 1 << 6,
		DepthBuffer = 1 << 7,
	};
	
	public ref class Map : NativeWrapper<mbgl::Map>
	{
	public:
		delegate System::Void StillImageCallback(System::Exception^ exception);

		Map(IRendererFrontend^ frontend);
		Map(IRendererFrontend^ frontend, MapObserver^ observer);
		Map(IRendererFrontend^ frontend, MapObserver^ observer, MapOptions_^ mapOptions);
		Map(IRendererFrontend^ frontend, MapObserver^ observer, MapOptions_^ mapOptions, ResourceOptions^ resourceOptions);
		Map(IRendererFrontend^ frontend, MapObserver^ observer, MapOptions_^ mapOptions, ResourceOptions^ resourceOptions, ClientOptions^ clientOptions);
		~Map();

		System::Void RenderStill(StillImageCallback^ callback);
		System::Void RenderStill(CameraOptions^ camera, MapDebugOptions debugOptions, StillImageCallback^ callback);
		System::Void TriggerRepaint();
		System::Void CancelTransitions();
        CameraOptions^ GetCameraOptions();
        CameraOptions^ GetCameraOptions(EdgeInsets^ padding);
        System::Void JumpTo(CameraOptions^ camera);
        System::Void EaseTo(CameraOptions^ camera, AnimationOptions^ animation);
        System::Void FlyTo(CameraOptions^ camera, AnimationOptions^ animation);
        System::Void MoveBy(ScreenCoordinate point);
        System::Void MoveBy(ScreenCoordinate point, AnimationOptions^ animation);
        System::Void ScaleBy(System::Double scale, System::Nullable<ScreenCoordinate> anchor);
        System::Void ScaleBy(System::Double scale, System::Nullable<ScreenCoordinate> anchor, AnimationOptions^ animation);
        System::Void PitchBy(System::Double pitch);
        System::Void PitchBy(System::Double pitch, AnimationOptions^ animation);
        System::Void RotateBy(ScreenCoordinate first, ScreenCoordinate second);
        System::Void RotateBy(ScreenCoordinate first, ScreenCoordinate second, AnimationOptions^ animation);
        
        CameraOptions^ CameraForLatLngBounds(
            LatLngBounds^ bounds,
            EdgeInsets^ padding
        );
        
        CameraOptions^ CameraForLatLngBounds(
            LatLngBounds^ bounds,
            EdgeInsets^ padding,
            System::Nullable<System::Double> bearing
        );
        
        CameraOptions^ CameraForLatLngBounds(
            LatLngBounds^ bounds,
            EdgeInsets^ padding,
            System::Nullable<System::Double> bearing,
            System::Nullable<System::Double> pitch
        );
        
        CameraOptions^ CameraForLatLngs(
            System::Collections::Generic::IEnumerable<LatLng^>^ latLngs,
            EdgeInsets^ padding
        );
        
        CameraOptions^ CameraForLatLngs(
            System::Collections::Generic::IEnumerable<LatLng^>^ latLngs,
            EdgeInsets^ padding,
            System::Nullable<System::Double> bearing
        );
        
        CameraOptions^ CameraForLatLngs(
            System::Collections::Generic::IEnumerable<LatLng^>^ latLngs,
            EdgeInsets^ padding,
            System::Nullable<System::Double> bearing,
            System::Nullable<System::Double> pitch
        );
        
        LatLngBounds^ LatLngBoundsForCamera(CameraOptions^ camera);
        LatLngBounds^ LatLngBoundsForCameraUnwrapped(CameraOptions^ camera);
        System::Void SetNorthOrientation(NorthOrientation orientation);
        System::Void SetConstrainMode(ConstrainMode mode);
        System::Void SetViewportMode(ViewportMode mode);
        System::Void SetSize(Size^ size);
        ScreenCoordinate PixelForLatLng(LatLng^ latLng);
        LatLng^ LatLngForPixel(ScreenCoordinate pixel);
        System::Collections::Generic::IEnumerable<ScreenCoordinate>^ PixelsForLatLngs(System::Collections::Generic::IEnumerable<LatLng^>^ latLngs);
        System::Collections::Generic::IEnumerable<LatLng^>^ LatLngsForPixels(System::Collections::Generic::IEnumerable<ScreenCoordinate>^ screenCoords);
        System::Void DumpDebugLogs();

        property Style_^ Style { Style_^ get(); System::Void set(Style_^ value); }
        property System::Boolean IsGestureInProgress { System::Boolean get(); System::Void set(System::Boolean value); }
        property System::Boolean IsRotating { System::Boolean get(); }
        property System::Boolean IsScaling { System::Boolean get(); }
        property System::Boolean IsPanning { System::Boolean get(); }
        property BoundOptions^ Bounds { BoundOptions^ get(); System::Void set(BoundOptions^ value); }
        property MapOptions_^ MapOptions { MapOptions_^ get(); }
        property ProjectionMode_^ ProjectionMode { ProjectionMode_^ get(); System::Void set(ProjectionMode_^ value); }
        property TransformState_^ TransformState { TransformState_^ get(); }
        property System::Byte PrefetchZoomDelta { System::Byte get(); System::Void set(System::Byte value); }
        property MapDebugOptions Debug { MapDebugOptions get(); System::Void set(MapDebugOptions value); }
        property System::Boolean IsFullyLoaded { System::Boolean get(); }
        property FreeCameraOptions_^ FreeCameraOptions { FreeCameraOptions_^ get(); System::Void set(FreeCameraOptions_^ value); }
    private:
		MapObserver^ _Observer;
        MapOptions_^ _MapOptions;
		ResourceOptions^ _ResourceOptions;
		ClientOptions^ _ClientOptions;
		Style_^ _Style;
	};
}
