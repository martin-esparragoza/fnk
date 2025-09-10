#include <stddef.h>
#include "elftofnk/include/vector.h"
#include "common/include/errc.h"

static const char* errcstr[] = {
    [ELFTOFNK_VECTOR_ERRC_FAILED_ALLOC - COMMON_ERRC_BASE] =      "Failed to allocate enough memory",
    [ELFTOFNK_VECTOR_ERRC_UNREACHABLE_INDEX - COMMON_ERRC_BASE] = "Index out of bounds",
    [ELFTOFNK_VECTOR_ERRC_ITER_END - COMMON_ERRC_BASE] =          "Iterator reached the end of vector"
};

/**
 * @brief Initialize and allocate a new vector
 * @param [in] vec Target vector
 * @param [in] initialsize Lengh of the base allocation
 * @retval ELFTOFNK_VECTOR_ERRC_FAILED_ALLOC If the initial allocation did not happen
 * @retval 0 if ok
 */
unsigned elftofnk_vector_init(struct elftofnk_vector* vec, size_t initialsize);

/**
 * @brief Get error string
 * @param [in] errc Error code
 * @param NULL if no error code found
 * @return Pointer to error string
 */
const char* elftofnk_vector_errctostr(unsigned errc);

/**
 * @brief Get a vector element
 * @note Using an iterator can be more performant because get will always check for in bounds (meaning that if you put it into a for loop it will check twice)
 * @note To set, just use the get function and then set the data ptr
 * @param [in] vec Target vector
 * @param [in] i Index to get
 * @param [out] data Will be set to point to the element. Unmodified if error
 * @return ELFTOFNK_VECTOR_ERRC_UNREACHABLE_INDEX If out of bounds index was supplied
 * @return 0 if ok
 */
// kms const
unsigned vector_get(const struct elftofnk_vector* vec, size_t i, void* const* data);

/**
 * @brief Start iterating starting at where data will now point
 * @param [in] vec Target vector
 * @param [out] data Will be set to point to the next element. Unmodified if error
 */
void vector_get_iter(const struct elftofnk_vector* vec, void** data);

/**
 * @brief Advance the iterator
 * @param [in] vec Target vector
 * @param [in,out] data Will be set to point to the next element. Unmodified if error
 * @retval ELFTOFNK_VECTOR_ITER_END Invalid iterator or the end was reached
 * @retval 0 if ok
 */
unsigned vector_iter(const struct elftofnk_vector* vec, void** data);

/**
 * @brief Set vector element to something
 * @param [in] vec Target vector
 * @param [in] data Data to be coppied to vector
 * @param [in] i Index of the element to be set
 * @retval ELFTOFNK_VECTOR_ERRC_UNREACHABLE_INDEX If out of bounds
 * @retval 0 if ok
 */
unsigned vector_set(const struct elftofnk_vector* vec, const void* data, size_t i);

/**
 * @brief Add element to the front of the vector
 * @param [in] vec Target vector
 * @param [in] data Data to be added to the vector
 * @retval ELFTOFNK_VECTOR_FAILED_ALLOC If could not resize the vector
 * @retval 0 if ok
 */
unsigned vector_push(const struct elftofnk_vector* vec, const void* data);

/**
 * @brief Deallocates a vector
 * @note Its a given that the vector is now garbage after this
 * @note If the free fails, you're cooked anyway...
 * @param [in] vec Target vector
 */
void elftofnk_vector_fini(struct elftofnk_vector* vec);