#ifndef PLUGINLOADER_FILESYSTEM_H
#define PLUGINLOADER_FILESYSTEM_H

#include <string>
#include <vector>

namespace Filesystem
{
	namespace Path
	{
		/// <summary>
		/// Gets the extension portion of a path, including the leading dot.
		/// </summary>
		/// <param name="path">The path to get the extension of.</param>
		/// <returns>The extension portion of the path including the leading dot, or an empty string if none.</returns>
		std::string getExtension(const std::string &path);

		/// <summary>
		/// Gets the filename portion of a path.
		/// </summary>
		/// <param name="path">The path to get the filename of.</param>
		/// <returns>The filename portion of the path, or an empty string if none.</returns>
		std::string getFilename(const std::string &path);

		/// <summary>
		/// Gets the filename portion of a path, excluding the extension.</param>
		/// </summary>
		/// <param name="path">The path to get the filename of.</param>
		/// <returns>The filename portion of the path without the extension, or an empty string if none.</returns>
		std::string getFilenameWithoutExtension(const std::string &path);

		/// <summary>
		/// Combines two paths into a complete path, putting a directory separator between them if necessary.
		/// </summary>
		/// <param name="left">The left side of the path.</param>
		/// <param name="right">The right side of the path.</param>
		/// <returns>The combined path.</returns>
		std::string combine(const std::string &left, const std::string &right);
	}

	namespace Directory
	{
		/// <summary>
		/// Determines if a directory exists.
		/// </summary>
		/// <param name="path">The path to the directory to check.</param>
		/// <returns><c>true</c> if the path exists and points to a directory.</returns>
		bool exists(const std::string &path);

		/// <summary>
		/// Enumerates through the files in a directory.
		/// </summary>
		/// <param name="path">The path to the directory to enumerate through.</param>
		/// <param name="results">The vector to store resulting paths to.</param>
		/// <returns><c>true</c> if successful.</returns>
		bool enumerate(const std::string &path, std::vector<std::string> *results);
	}

	namespace File
	{
		/// <summary>
		/// Determines if a file exists.
		/// </summary>
		/// <param name="path">The path to the file to check.</param>
		/// <returns><c>true</c> if the path exists and points to a file.</returns>
		bool exists(const std::string &path);
	}
}

#endif // PLUGINLOADER_FILESYSTEM_H