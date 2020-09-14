**a. Removing all owner permissions from a file denies the file owner access, even though group and other do have access.**
~~~console
$ touch file.txt                        # Create a file
$ chmod u-rwx file.txt                  # Remove owner's all permissions
$ ls -l file.txt                        # Check the permission bits
----rw-r--. 1 digvijay digvijay 0 Sep  2 17:06 file.txt
$ echo "something" > file.txt           # Try writing something to file - failes
-bash: file.txt: Permission denied
~~~

**b. On a directory with read permission but not execute permission, the names of files in the directory can be listed, but the files themselves can’t be accessed, regardless of the permissions on them.**
~~~console
$ mkdir dir                             # Create a directory
$ touch dir/file.txt                    # Create a file inside `dir'
$ chmod u-x dir                         # Remove owner's execute permission
$ ls -l                                 # Check the directory persmission bits
total 0
drw-rwxr-x. 2 digvijay digvijay 22 Sep  2 17:35 dir
$ command ls dir/                       # list the file inside directory - works
file.txt
$ echo "something" > dir/file.txt       # Try writing something to file - fails
-bash: dir/file.txt: Permission denied
~~~

**What permissions are required on the parent directory and the file itself in order to create a new file, open a file for reading, open a file for writing, and delete a file? What permissions are required on the source and target directory to rename a file? If the target file of a rename operation already exists, what permissions are required on that file? How does setting the sticky permission bit (chmod +t) of a directory affect renaming and deletion operations?**
Execute the script that loops over the permissions and tries to do opearations on the file (create, read, write, delete or move)
~~~console
$ mkdir dir
$ bash perm_demo.sh create 2>/dev/null
operation successful with dir permission 300        # Create requires Execute (search) and Write permissions on the parent direcrory
$ bash perm_demo.sh read 2>/dev/null
operation successful with file permission 400       # Read requires Read permission on the file
operation successful with dir permission 100        # Read requires Execute permission on the parent directory
$ bash perm_demo.sh write 2>/dev/null
operation successful with file permission 200       # Write requires Write permission on the file
operation successful with dir permission 100        # Write requires Execute permission on the parent directory
$ bash perm_demo.sh delete 2>/dev/null
operation successful with file permission 0         # Delete doesn't require any permissions on the file itself
operation successful with dir permission 300        # Delete requires Execute (search) and Write permissions on the parent direcrory
$ bash perm_demo.sh move 2>/dev/null
operation successful with file permission 0         # Move doesn't require any permissions on the file itself
operation successful with dir permission 300        # Move requires Execute (search) and Write permissions on both the parent directories
~~~

If the parent directory has sticky bit set, then along with above permissions user also needs to be the owner of the file
~~~console
$ bash perm_demo.sh create 2>/dev/null
operation successful with dir permission 300
$ chmod +t dir/
$ sudo chown -R root dir
$ mv dir/file.txt dir/file2.txt                     # Fails as owner is root and user is digvijay
mv: failed to access ‘dir/file2.txt’: Permission denied
$ sudo chown -R digvijay dir
$ mv dir/file.txt dir/file2.txt                     # Succeeds as user digvijay is the owner
$
~~~
