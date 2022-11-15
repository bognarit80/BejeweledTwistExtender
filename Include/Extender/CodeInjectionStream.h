#ifndef PLUGINLOADER_CODEINJECTIONSTREAM_H
#define PLUGINLOADER_CODEINJECTIONSTREAM_H

#include <cstdint>

#ifndef _WIN32
#include <sys/types.h>
#endif

namespace CodeInjection
{
	class CodeInjectionStream
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="CodeInjectionStream"/> class.
		/// The stream will operate on a block of code in memory.
		/// </summary>
		/// <param name="start">The start address of the code.</param>
		/// <param name="size">The size of the code.</param>
		CodeInjectionStream(void *start, size_t size);

		/// <summary>
		/// Finalizes an instance of the <see cref="CodeInjectionStream"/> class.
		/// The stream will be flushed if necessary.
		/// </summary>
		~CodeInjectionStream();

		/// <summary>
		/// Writes data to the stream at the current position, advancing the stream by the size of the data.
		/// </summary>
		/// <param name="data">The data to write.</param>
		/// <param name="dataSize">The size of the data to write. It must fit.</param>
		/// <returns><c>true</c> if the data was written successfully.</returns>
		bool write(const void *data, size_t dataSize);

		/// <summary>
		/// Reads data from the stream at the current position, advancing the stream by the size of the data.
		/// </summary>
		/// <param name="out">The buffer to write data to.</param>
		/// <param name="size">The number of bytes to read.</param>
		/// <returns><c>true</c> if the data was read successfully.</param>
		bool read(void *out, size_t size);

		/// <summary>
		/// Reads a relative 32-bit jump or call instruction from the stream at the current position, advancing the stream by the size of the instruction.
		/// </summary>
		/// <returns>The target of the far jump or call if valid, or <c>NULL</c> otherwise.</returns>
		void* readRel32Jump();

		/// <summary>
		/// Reads a relative 32-bit jump or call instruction from the stream at the current position without advancing the stream position.
		/// </summary>
		/// <returns>The target of the far jump or call if valid, or <c>NULL</c> otherwise.</returns>
		void* peekRel32Jump() const;

		/// <summary>
		/// Writes a relative 32-bit jump instruction to the stream at the current position, advancing the stream by the size of the instruction.
		/// </summary>
		/// <param name="target">The target of the far jump instruction to write.</param>
		/// <returns><c>true</c> if the jump was written successfully.</returns>
		bool writeRel32Jump(void *target);

		/// <summary>
		/// Writes a relative 32-bit call instruction to the stream at the current position, advancing the stream by the size of the instruction.
		/// </summary>
		/// <param name="target">The target of the far call instruction to write.</param>
		/// <returns><c>true</c> if the call was written successfully.</returns>
		bool writeRel32Call(void *target);

		/// <summary>
		/// Writes NOP instructions to the stream at the current position, advancing the stream by the size of the data written.
		/// </summary>
		/// <param name="count">The number of NOP instructions to write. Each instruction is one byte large.</param>
		/// <returns><c>true</c> if the instructions were written successfully.</returns>
		bool writeNops(int count);

		/// <summary>
		/// Seeks to an offset from the beginning of the stream's data block.
		/// </summary>
		/// <param name="offset">The offset to seek to. It must be inside the data block.</param>
		/// <returns><c>true</c> if the seek was successful.</returns>
		bool seekTo(size_t offset);

		/// <summary>
		/// Seeks to a pointer inside the stream's data block.
		/// </summary>
		/// <param name="ptr">The pointer to seek to. It must be inside the data block.</param>
		/// <returns><c>true</c> if the seek was successful.</returns>
		bool seekTo(const void *ptr);

		/// <summary>
		/// Skips a number of bytes.
		/// </summary>
		/// <param name="count">The maximum number of bytes to skip.</param>
		/// <returns>The actual number of bytes that were skipped.</returns>
		size_t skip(size_t count);

		/// <summary>
		/// Commits any changes made to the code block.
		/// </summary>
		void flush();

		/// <summary>
		/// Gets the starting pointer of the stream's data block.
		/// </summary>
		/// <returns>The starting pointer of the stream's data block.</returns>
		void *getStart() const { return start; }

		/// <summary>
		/// Gets the current offset of the stream from the start of its data block.
		/// </summary>
		/// <returns>The current offset of the stream.</returns>
		size_t getOffset() const { return currentPtr - start; }

		/// <summary>
		/// Gets the size of the data block that the stream operates on.
		/// </summary>
		/// <returns>The size of the data block.</returns>
		size_t getSize() const { return size; }

		/// <summary>
		/// Determines whether or not the stream is at the end of its data block.
		/// </summary>
		/// <returns><c>true</c> if the stream is at the end of its data block.</returns>
		bool isAtEnd() const { return static_cast<size_t>(currentPtr - start) == size; }

		/// <summary>
		/// The size of a jump instruction written by <see cref="writeRel32Jump"/> and <see cref="writeRel32Call"/>.
		/// </summary>
		static const int Rel32JumpSize = 5;

	private:
		uint8_t *start;
		uint8_t *currentPtr;
		size_t size;
		bool needsFlush;
		int oldProtection;

		/// <summary>
		/// Determines whether or not a given amount of space is available in the stream.
		/// </summary>
		/// <param name="sizeNeeded">The size.</param>
		/// <returns><c>true</c> if space is available.</returns>
		bool isSpaceAvailable(size_t sizeNeeded) const { return (size - getOffset()) >= sizeNeeded; }

		/// <summary>
		/// Writes a relative 32-bit jump instruction.
		/// </summary>
		/// <param name="opcode">The opcode.</param>
		/// <param name="target">The target.</param>
		/// <returns><c>true</c> if the jump was written successfully.</returns>
		bool writeRel32Jump(uint8_t opcode, void *target);

		/// <summary>
		/// Unprotects the stream's data block and allows the code inside it to be manipulated.
		/// </summary>
		void unprotect();

		/// <summary>
		/// Restores the stream's data block's protection to its original setting.
		/// </summary>
		void protect();
	};
}

#endif
