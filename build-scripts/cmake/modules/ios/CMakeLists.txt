project( iscool-ios )

include( declare-iscool-library )

declare_iscool_library( NAME ios
  FILES
  "get_bundle_id.mm"
  "get_device_model.mm"
  "get_root_view_controller.mm"
  "present_view_controller.mm"
  "std_to_nsstring.mm"
  "system_version.mm"
  )
