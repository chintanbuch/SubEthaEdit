﻿<?Lassoscript
// Last modified 11/2/09 by ECL, Landmann InterActive

// CHANGE NOTES
// 1/15/09
// First implementation
// 11/2/09
// Changed path to ckeditor to remove extra leading slash

If: $svDebug == 'Y';
	'<p class="debug"><strong>/admin/frm_story</strong></p>\n';
/If;

// Convert action_params
Include:'story_params.inc';

// Defining the DataType
Var:'vDataType' = 'Story';

// If Edit page, get the record
If: (Response_Filepath) >> 'setup_editrecord.lasso';

	// If Process = Y, form was submit, so update the record
	// Otherwise, it is a new edit so get the record
	If: $vProcess != 'Y';

		// If error 1021, action was a successful delete, so display error and abort right away
		If: $vError == '1021';
			LI_ShowError3: -ErrNum=$vError, -Option=$vOption;
			Abort;
		/If;

		// Get the record
		Var:'SQLGetStory' = 'SELECT * FROM ' $svStoriesTable ' WHERE ID = "' $vID '" LIMIT 1';
		Inline: $IV_Stories, -Table=$svStoriesTable, -SQL=$SQLGetStory;

			If: $svDebug == 'Y';
				'<p class="debug">32: Error_CurrentError = ' (Error_CurrentError) '</p>\n';
			/If;

			// If Found_Count is wrong, the wrong User ID was passed, so dump out 2000 "No Record Found"	
			If: (Found_Count) == 0;
				$vError = '2000';
				LI_ShowError3: -ErrNum=$vError, -Option=$vOption;
				If: $svDebug == 'Y';
					Include:($svLibsPath)'vardumpalpha.lasso';
				/If;
				Abort;
			/If;
			Var:'vStory_Head' = (Field:'Story_Head');
			Var:'vStory_Comment' = (Field:'Story_Comment');
			Var:'vStory_Name' = (Field:'Story_Name');
			Var:'vStory_Thumb' = (Field:'Story_Thumb');
			Var:'vActive' = (Field:'Active');
			Var:'vDateModified' = (Field:'DateModified');
		/Inline;

		// If there is an error, dump out error 1012 "Update Failed"
		If: (Error_CurrentError) != 0;
			$vError = '2000';
		/If;

	/If;
	
/If;

If: (Var:'vID') == '';
	'<h2>'(LI_ShowIconByDataType)'&nbsp;&nbsp;Add Story</h2>\n';
Else;
	'<h2>'(LI_ShowIconByDataType)'&nbsp;&nbsp;Edit Story</h2>\n';
/If;

// Standard Error Table
If: $vError != '';
	LI_ShowError3: -ErrNum=$vError, -Option=$vOption;
/If;
?>
<form action="setup_addresponse.lasso" method="post">
	<table width="500">
		<tr>
			<td width="90" class="tablehead_10_white_right">Headline</td>
			<td width="410" bgcolor="#f0f0f0">
				<input type="text" name="Story_Head" value="[$vStory_Head]" size="32" maxlength="255">
			</td>
		</tr>
		<tr>
			<td width="90" class="tablehead_10_white_right">Name</td>
			<td width="410" bgcolor="#f0f0f0">
				<input type="text" name="Story_Name" value="[$vStory_Name]" size="32" maxlength="255">
			</td>
		</tr>
		<tr>
			<td width="90" class="tablehead_10_white_right">Story Text[$svInputRequired]</td>
			<td width="410" bgcolor="#f0f0f0">
				<textarea name="Story_Comment">[$vStory_Comment]</textarea>
			</td>
		</tr>
<!-- Activate CKEditor for the Text field -->
<script type="text/javascript">
	CKEDITOR.replace( 'Story_Comment' );
</script>
		<tr>
			<td width="90" class="tablehead_10_white_right">Thumbnail</td>
			<td width="410" bgcolor="#f0f0f0">
<?Lassoscript   
Var:'image_thumb_array' = (File_ListDirectory: ($svImagesThmbPath));
If: Var:'image_thumb_array' >> '.DS_Store';
	$image_thumb_array->(Remove:1);
/If;
	'\t\t\t<select name="Story_Thumb">\n';
	'\t\t\t\t<option value=""'; If: (Var:'vStory_Thumb') == ''; ' selected'; /If; '></option>\n';
		Iterate: $image_Thumb_array, (var:'temp_Thumb');
			'\t\t\t\t\t<option value="'($temp_Thumb) '"'; If: (Var:'vStory_Thumb') == ($temp_Thumb); ' selected'; /If; '>'($temp_Thumb)'</option>\n';
		/Iterate;
	'\t\t\t</select>\n';
?>			</td>
		</tr>
		<tr>
			<td width="120" class="tablehead_10_white_right">Active[$svInputRequired]</td>
			<td width="280" bgcolor="#f0f0f0">
				<input type="radio" name="Active" value="Y"[If: (Var:'vActive') == 'Y' || (Var:'vActive') == ''] checked[/If]>Yes&nbsp;&nbsp;
				<input type="radio" name="Active" value="N"[If: (Var:'vActive') == 'N'] checked[/If]>No
			</td>
		</tr>
[If: (Response_Filepath) >> 'setup_edit' || (Response_Filepath) >> 'setup_search']
		<tr>
			<td width="120" class="tablehead_10_white_right">Date Modified</td>
			<td width="280" bgcolor="#f0f0f0">
				[Var:'vDateModified']
			</td>
		</tr>
[/If]
		<tr>
			<td colspan="2" bgcolor="#666666">
				<div align="center">
<?Lassoscript
// If Edit page, add a hidden field to show check if page is submit
If: (Response_Filepath) >> 'editrecord';
				'\t\t\t\t<input type="hidden" name="Process" value="Y">\n';
				'\t\t\t\t<input type="hidden" name="ID" value="'($vID)'">\n';
				'\t\t\t\t<input type="hidden" name="DataType" value="Story">\n';
				'\t\t\t\t<input type="submit" name="Action" value="Update">\n';
				'\t\t\t\t<input type="submit" name="Action" value="Delete" onClick="return confirmDeleteContent()">\n';
Else;
				'\t\t\t\t<input type="submit" name="Action" value="Add">\n';
				'\t\t\t\t<input type="hidden" name="DataType" value="Story">\n';
/If; ?>			</div>
			</td>
		</tr>
	</table>
</form>
<br>