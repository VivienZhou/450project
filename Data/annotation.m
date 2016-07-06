folder = 'coins';
template = imread(fullfile(folder, '1_model.png'));
scaleRow = size(template, 1);
scaleCol = size(template, 2);
 
 fid = fopen(fullfile(folder, 'result.csv'));
 tline = fgetl(fid);
 tline = fgetl(fid);
 
 while ischar(tline)
     row = strread(tline, '%s', 'delimiter', ',');
     imgFilename = row{1};
     objectInfo = {};
     for i = 2 : 3: size(row)
         if strcmp(row{i}, '')
             break
         end
         objectInfo{(i + 1) / 3} = struct('row', str2num(row{i}), 'col', str2num(row{i + 1}), 'rotation', str2num(row{i + 2}), 'scaleCol', scaleCol, 'scaleRow', scaleRow);
     end
     drawBoundary(objectInfo, fullfile(folder, imgFilename));
     tline = fgetl(fid);
 end
 
 fclose(fid);