pub struct RawVec<T> {
    ptr: Unique<T>,
    cap: usize,
}

/// Converts a `Box<[T]>` into a `RawVec<T>`.
pub fn from_box(slice: Box<[T], A>) -> Self {
    unsafe {
        let (slice, alloc) = Box::into_raw_with_allocator(slice);
        RawVec::from_raw_parts_in(slice.as_mut_ptr(), slice.len(), alloc)
    }
}

/// Converts the entire buffer into `Box<[MaybeUninit<T>]>` with the specified `len`.
///
/// Note that this will correctly reconstitute any `cap` changes
/// that may have been performed. (See description of type for details.)
///
/// # Safety
///
/// * `len` must be greater than or equal to the most recently requested capacity, and
/// * `len` must be less than or equal to `self.capacity()`.
///
/// Note, that the requested capacity and `self.capacity()` could differ, as
/// an allocator could overallocate and return a greater memory block than requested.
pub unsafe fn into_box(self, len: usize) -> Box<[MaybeUninit<T>], A> {
    // Sanity-check one half of the safety requirement (we cannot check the other half).
    debug_assert!(
        len <= self.capacity(),
        "`len` must be smaller than or equal to `self.capacity()`"
    );

    let me = ManuallyDrop::new(self);
    unsafe {
        let slice = slice::from_raw_parts_mut(me.ptr() as *mut MaybeUninit<T>, len);
        Box::from_raw_in(slice, ptr::read(&me.alloc))
    }
}