# Folder Deduplicator

You’re given a virtual folder tree where some subfolders may be duplicates (i.e., have the exact same structure and file names). Your job is to detect and remove all duplicate subtrees.

## Input

You're given a tree-like structure where each node is a DirNode representing a folder. Each folder has:

    A name (string)

    A list of children (other DirNodes)

Some subtrees are structurally identical. Your job is to detect duplicate folder structures and delete all but one instance of them.

## Output

After deduplication, print the cleaned folder structure using indentation like before.

## Example

Here’s the tree as a list of folder paths:

/a/b/c
/a/b/d
/e/b/c
/e/b/d
/f

The /a/b and /e/b subtrees are identical. After deduplication, remove /e/b, and the final tree should be:

a
	b
		c
		d
e
f

## Constraints

    Folder names are unique per level but not globally.

    Structure matters: folders /x/y/z and /p/y/z are duplicates only if all subfolders match recursively.

    Use hashing or serialization to detect duplicates.
