#include <Extender/Filesystem.h>

namespace
{
#ifdef _WIN32
	const std::string PreferredSeparator = "\\";
	const std::string AllowedSeparators = "\\/";
#else
	const std::string PreferredSeparator = "/";
	const std::string AllowedSeparators = "/";
#endif
}

namespace Filesystem
{
	namespace Path
	{
		/// <summary>
		/// Gets the extension portion of a path, including the leading dot.
		/// </summary>
		/// <param name="path">The path to get the extension of.</param>
		/// <returns>The extension portion of the path including the leading dot, or an empty string if none.</returns>
		std::string getExtension(const std::string &path)
		{
			size_t dotPos = path.find_last_of('.');
			if (dotPos == std::string::npos)
				return "";
			return path.substr(dotPos);
		}

		/// <summary>
		/// Gets the filename portion of a path.
		/// </summary>
		/// <param name="path">The path to get the filename of.</param>
		/// <returns>The filename portion of the path, or an empty string if none.</returns>
		std::string getFilename(const std::string &path)
		{
			size_t lastSlashPos = path.find_last_of(AllowedSeparators);
			if (lastSlashPos == std::string::npos)
				return path;
			return path.substr(lastSlashPos + 1);
		}

		/// <summary>
		/// Gets the filename portion of a path, excluding the extension.</param>
		/// </summary>
		/// <param name="path">The path to get the filename of.</param>
		/// <returns>The filename portion of the path without the extension, or an empty string if none.</returns>
		std::string getFilenameWithoutExtension(const std::string &path)
		{
			size_t lastSlashPos = path.find_last_of(AllowedSeparators);
			size_t nameStartPos = 0;
			if (lastSlashPos != std::string::npos)
				nameStartPos = lastSlashPos + 1;
			size_t dotPos = path.find_last_of('.');
			if (dotPos < nameStartPos)
				return path.substr(nameStartPos);
			return path.substr(nameStartPos, dotPos - nameStartPos);
		}

		/// <summary>
		/// Combines two paths into a complete path, putting a directory separator between them if necessary.
		/// </summary>
		/// <param name="left">The left side of the path.</param>
		/// <param name="right">The right side of the path.</param>
		/// <returns>The combined path.</returns>
		std::string combine(const std::string &left, const std::string &right)
		{
			if (left.length() == 0)
				return right;
			if (right.length() == 0)
				return left;
			char leftEnd = left[left.length() - 1];
			char rightStart = right[0];
			if (AllowedSeparators.find(leftEnd) != std::string::npos
				|| AllowedSeparators.find(rightStart) != std::string::npos)
				return left + right; // A separator already exists between the two paths
			return left + PreferredSeparator + right;
		}
	}
}