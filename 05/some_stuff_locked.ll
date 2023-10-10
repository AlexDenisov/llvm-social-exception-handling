declare void @some_stuff()
declare void @acquire_lock()
declare void @release_lock()
declare void @rethrow()

define void @some_stuff_locked() personality ptr @llvm_social_personality {
  call void @acquire_lock()
  invoke void @some_stuff()
    to label %defer
    unwind label %landing_pad

landing_pad:
  %unused = landingpad { ptr, i32 } cleanup
  call void @release_lock()
  call void @rethrow()
  unreachable

defer:
  call void @release_lock()
  ret void
}

declare i32 @llvm_social_personality(...)