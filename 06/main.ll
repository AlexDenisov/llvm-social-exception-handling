; ModuleID = 'main.cpp'
source_filename = "main.cpp"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-macosx13.0.0"

@_ZTIi = external constant ptr

; Function Attrs: noinline norecurse optnone ssp uwtable(sync)
define i32 @main() #0 personality ptr @__gxx_personality_v0 {
  %1 = alloca i32, align 4
  %2 = alloca ptr, align 8
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  invoke void @_Z3foov()
          to label %5 unwind label %6

5:                                                ; preds = %0
  br label %20

6:                                                ; preds = %0
  %7 = landingpad { ptr, i32 }
          catch ptr @_ZTIi
          catch ptr null
  %8 = extractvalue { ptr, i32 } %7, 0
  store ptr %8, ptr %2, align 8
  %9 = extractvalue { ptr, i32 } %7, 1
  store i32 %9, ptr %3, align 4
  br label %10

10:                                               ; preds = %6
  %11 = load i32, ptr %3, align 4
  %12 = call i32 @llvm.eh.typeid.for(ptr @_ZTIi) #4
  %13 = icmp eq i32 %11, %12
  br i1 %13, label %14, label %21

14:                                               ; preds = %10
  %15 = load ptr, ptr %2, align 8
  %16 = call ptr @__cxa_begin_catch(ptr %15) #4
  %17 = load i32, ptr %16, align 4
  store i32 %17, ptr %4, align 4
  %18 = load i32, ptr %4, align 4
  invoke void @_Z3bazi(i32 noundef %18)
          to label %19 unwind label %30

19:                                               ; preds = %14
  call void @__cxa_end_catch() #4
  br label %20

20:                                               ; preds = %19, %24, %5
  ret i32 0

21:                                               ; preds = %10
  %22 = load ptr, ptr %2, align 8
  %23 = call ptr @__cxa_begin_catch(ptr %22) #4
  invoke void @_Z3barv()
          to label %24 unwind label %25

24:                                               ; preds = %21
  call void @__cxa_end_catch()
  br label %20

25:                                               ; preds = %21
  %26 = landingpad { ptr, i32 }
          cleanup
  %27 = extractvalue { ptr, i32 } %26, 0
  store ptr %27, ptr %2, align 8
  %28 = extractvalue { ptr, i32 } %26, 1
  store i32 %28, ptr %3, align 4
  invoke void @__cxa_end_catch()
          to label %29 unwind label %39

29:                                               ; preds = %25
  br label %34

30:                                               ; preds = %14
  %31 = landingpad { ptr, i32 }
          cleanup
  %32 = extractvalue { ptr, i32 } %31, 0
  store ptr %32, ptr %2, align 8
  %33 = extractvalue { ptr, i32 } %31, 1
  store i32 %33, ptr %3, align 4
  call void @__cxa_end_catch() #4
  br label %34

34:                                               ; preds = %30, %29
  %35 = load ptr, ptr %2, align 8
  %36 = load i32, ptr %3, align 4
  %37 = insertvalue { ptr, i32 } undef, ptr %35, 0
  %38 = insertvalue { ptr, i32 } %37, i32 %36, 1
  resume { ptr, i32 } %38

39:                                               ; preds = %25
  %40 = landingpad { ptr, i32 }
          catch ptr null
  %41 = extractvalue { ptr, i32 } %40, 0
  call void @__clang_call_terminate(ptr %41) #5
  unreachable
}

declare void @_Z3foov() #1

declare i32 @__gxx_personality_v0(...)

; Function Attrs: nounwind readnone
declare i32 @llvm.eh.typeid.for(ptr) #2

declare ptr @__cxa_begin_catch(ptr)

declare void @_Z3barv() #1

declare void @__cxa_end_catch()

; Function Attrs: noinline noreturn nounwind
define linkonce_odr hidden void @__clang_call_terminate(ptr %0) #3 {
  %2 = call ptr @__cxa_begin_catch(ptr %0) #4
  call void @_ZSt9terminatev() #5
  unreachable
}

declare void @_ZSt9terminatev()

declare void @_Z3bazi(i32 noundef) #1

attributes #0 = { noinline norecurse optnone ssp uwtable(sync) "frame-pointer"="non-leaf" "min-legal-vector-width"="0" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+sha3,+sm4,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a,+zcm,+zcz" }
attributes #1 = { "frame-pointer"="non-leaf" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+sha3,+sm4,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a,+zcm,+zcz" }
attributes #2 = { nounwind readnone }
attributes #3 = { noinline noreturn nounwind }
attributes #4 = { nounwind }
attributes #5 = { noreturn nounwind }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 14, i32 0]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 1}
!5 = !{!"Apple clang version 15.0.0 (clang-1500.0.40.1)"}
