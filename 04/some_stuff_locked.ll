declare void @some_stuff()
declare void @acquire_lock()
declare void @release_lock()

define void @some_stuff_locked() {
  call void @acquire_lock()
  call void @some_stuff()
  call void @release_lock()
  ret void
}