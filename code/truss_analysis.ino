C = [1 0 0 0 0 0 0 0 1 0 0 0 0 0 0;  % J1
     1 1 0 0 0 0 0 0 0 0 0 0 1 1 1;  % J2
     0 1 1 0 0 0 0 0 0 1 1 1 0 0 0;  % J3
     0 0 1 1 0 0 0 0 0 0 0 0 0 0 0;  % J4
     0 0 0 1 1 0 0 0 0 1 0 0 0 0 0;  % J5
     0 0 0 0 1 1 0 0 0 0 1 0 0 0 0;  % J6
     0 0 0 0 0 1 1 0 0 0 0 1 1 0 0;  % J7
     0 0 0 0 0 0 1 1 0 0 0 0 0 1 0;  % J8
     0 0 0 0 0 0 0 1 1 0 0 0 0 0 1]; % J9
Sx = [1; 0; 0; 0; 0; 0; 0; 0; 0];
Sy = [1; 0; 0; 1; 0; 0; 0; 0; 0];
X = [0; 12.5; 19.5; 31; 30; 23; 16; 9; 2];
Y = [0; 0; 0; 0; 7; 8; 8; 8; 7;];
L = [0; 0; 0; 32; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0;];



figure;
hold on;
grid on;

for i = 1:numMembers

    joints = find(C(:,i));

    x1 = X(joints(1));
    y1 = Y(joints(1));

    x2 = X(joints(2));
    y2 = Y(joints(2));

    plot([x1 x2],[y1 y2], ...
        'k','LineWidth',2);

    % midpoint of member
    mx = (x1+x2)/2;
    my = (y1+y2)/2;

    % member number
    text(mx,my+0.6,...
        sprintf('M%d',i),...
        'FontWeight','bold',...
        'Color','b');

    % member force
    if memberForcesScaled(i) >= 0
        forceType = 'T';
    else
        forceType = 'C';
    end

    text(mx,my-0.6,...
        sprintf('%.3f %s', ...
        abs(memberForcesScaled(i)), ...
        forceType),...
        'FontSize',8,...
        'Color','r');

end

% joints
plot(X,Y,'ko','MarkerFaceColor','k');

% joint labels
for i = 1:length(X)

    text(X(i)+0.4,Y(i)+0.4,...
        sprintf('J%d',i),...
        'FontWeight','bold');

    text(X(i)+0.4,Y(i)-0.8,...
        sprintf('(%.1f, %.1f)',...
        X(i),Y(i)),...
        'FontSize',8);

end

% supports
plot(X(Sx==1),Y(Sx==1),...
    'g^','MarkerSize',12,...
    'LineWidth',2);

plot(X(Sy==1),Y(Sy==1),...
    'g^','MarkerSize',12,...
    'LineWidth',2);

title('Final Truss Design');
xlabel('X Coordinate (in)');
ylabel('Y Coordinate (in)');
axis equal;
%**End Vis**
%finds the number of joins, members, and support reactions
numJoints = size(C, 1);
numMembers = size(C, 2);
numReactions = sum(Sx) + sum(Sy);
%sets the matrix of Sx and Sy
xReaction = numMembers + 1;
yReaction = [numMembers + 2, numMembers + 3];
%starts a counter for the y support reaction
yReactionCounter = 1;
% Construct the A matrix
A = zeros(2*numJoints, numMembers + numReactions);
%sets the matrix with the joints
for joint = 1:numJoints
 %sets the matrix with the members
 for member = 1:numMembers
     %searches for joints
     if C(joint, member) == 1
         other_joint = find(C(:, member) == 1 & (1:numJoints)' ~= joint);
         %finds the deltas of joints in the x and y direction
         deltaX = X(other_joint) - X(joint);
         deltaY = Y(other_joint) - Y(joint);
         %distance of the joints from eachother
         r = sqrt(deltaX^2 + deltaY^2);
         %distance of joints in the x and y direction
         xCoeff = deltaX / r;
         yCoeff = deltaY / r;
         %puts the x values in the odd rows
         A(2 * joint - 1, member) = xCoeff;
         %puts the y values in the even rows
         A(2 * joint, member) = yCoeff;
     end
 end
 %puts reaction forces in necessary location on the A matrix
 if Sx(joint)
     A(2 * joint - 1, xReaction) = 1;
 end
 if Sy(joint)
     A(2 * joint, yReaction(yReactionCounter)) = 1;
     yReactionCounter = yReactionCounter + 1;
 end
end
% Solve for the T array of unknown sources
T = A \ L;
% takes the members and support reactions form T matrix
memberForces = T(1:numMembers);
supportReactions = T(numMembers + 1:end);
% creates a matrix to store the legnths of all the members
memberLengths = zeros(numMembers, 1);
% Calculate the lengths of every force member
for member = 1:numMembers
 joints = find(C(:, member));
 deltaX = X(joints(2)) - X(joints(1));
 deltaY = Y(joints(2)) - Y(joints(1));
 memberLengths(member) = sqrt(deltaX^2 + deltaY^2);
end
% Calculate the critical forces (Pcrit) with lengths of members
PCrit = -3054.789 * (memberLengths .^ -2.009);
% Find negative forces (compression)
NegForce = (T < 0) & (abs(T) > 1e-10); % 1e-10 is a small threshold to distinguish from zero
NegVal = T(NegForce);
NegVal_Index = find(NegForce);
PCrit_neg = PCrit(NegForce);
%NegForce = T < 0;
%NegVal = T(NegForce);
%PCrit_neg = PCrit(NegForce);
% Finds the value of the loaded weight
weightOnJoint = sum(L);
% Calculate load ratios (Rc)
Rc = (NegVal) ./ weightOnJoint;
% Calculate maximum theoretical load (Wfailure) for each negative force
Wfailure = zeros(size(NegVal));
for i = 1:length(NegVal)
 Wfailure(i) = PCrit_neg(i) ./ Rc(i);
end
%finds the smallest values of Wfailure to find the max theoretcal weight
[FailureWeight, FailureWeightIndex] = min(Wfailure);
criticalMemberIndex = NegVal_Index(FailureWeightIndex);
scaleFactor = FailureWeight / weightOnJoint;
memberForcesScaled = memberForces * scaleFactor;
% prints the heading and the load weight
fprintf('\n EK301, Section A2, Group 15: Abou-Ezzi C., Lopez M., Nayana A. 4/05/2024. \n \n')
fprintf('Load: %.2f oz \n \n', weightOnJoint)
% Prints the magnitude of every member force in a column
fprintf('Member forces in oz:\n \n');
% if the member is negative, prints (C), if poisitve, prints (T)
for i = 1:numMembers
 fprintf('m%d: %.3f (', i,abs(memberForcesScaled(i)));
 if memberForcesScaled(i) >= 0
 %if memberForces(i) >= 0
     fprintf('T)\n \n');
 else
     fprintf('C)\n \n');
 end
end
%prints the reaction forces in a column
fprintf('Reaction forces in oz:\n \n');
fprintf('Sx1: %.1f\n \n', supportReactions(1));
fprintf('Sy1: %.2f\n \n', supportReactions(2));
fprintf('Sy2: %.2f\n \n', supportReactions(3));
fprintf('Member %d will be the first to fail. \n', criticalMemberIndex)
fprintf('Thus giving the truss, a theoretical max load of: %.3f oz \n \n', FailureWeight)
% prints the cost of the truss
cost = 10*numJoints + sum(memberLengths)*1;
fprintf('Cost of truss: $%.2f\n \n', cost);
% Calculate the theoretical max load/cost ratio
max_load_cost_ratio = FailureWeight / cost;
fprintf('Theoretical max load/cost ratio in oz/$: %.4f\n', max_load_cost_ratio);

fprintf('\n');
fprintf('Member\tLength\tType\tForce @ %.3f oz\n',FailureWeight);
fprintf('-------------------------------------------------\n');

for i = 1:numMembers

    if memberForcesScaled(i) >= 0
        type = 'Tension';
    else
        type = 'Compression';
    end

    fprintf('M%d\t%.1f\t%s\t%.3f\n',...
        i,...
        memberLengths(i),...
        type,...
        abs(memberForcesScaled(i)));

end



