function drawBoundary_test(objectInfo, imgFilename)
    % objectInfo is a list of cell, each cell is a struct which contains 5
    % fields: col, row, rotation, scaleCol, scaleRow
    img = imread(imgFilename);
    
    figure; imshow(img); hold on;
    folder = 'coins';
    template = imread(fullfile(folder, '1_model.png'));
    figure; imshow(imresize(template, 0.1)); hold on;
        col = objectInfo.col;
        row = objectInfo.row;
        scaleCol = objectInfo.scaleCol;
        scaleRow = objectInfo.scaleRow;
        rotation = objectInfo.rotation;
        
    %for i = 1 : size(objectInfo, 2)
%         col = objectInfo{i}.col;
%         row = objectInfo{i}.row;
%         scaleCol = objectInfo{i}.scaleCol;
%         scaleRow = objectInfo{i}.scaleRow;
%         rotation = objectInfo{i}.rotation;
        % plot(objectInfo{i}.col, objectInfo{i}.row,'r.','MarkerSize',20);
        % draw a rectangle
        plot(objectInfo.col, objectInfo.row,'r.','MarkerSize',20);
        coord(1, :) = [- scaleCol/2, scaleCol/2, scaleCol/2, - scaleCol/2, - scaleCol/2];
        coord(2, :) = [- scaleRow/2, - scaleRow/2, scaleRow/2, scaleRow/2, - scaleRow/2];
        alpha = - rotation;
        rotatedCoord = [cos(alpha), -sin(alpha); sin(alpha), cos(alpha)] * coord;
        plot(rotatedCoord(1,:) + col, rotatedCoord(2,:) + row,'r');
    %end
    [pathstr,name,~] = fileparts(imgFilename);
    saveas(gcf, fullfile(pathstr, [name, 'test']), 'png');
    hold off;
end